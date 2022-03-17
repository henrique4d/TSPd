#include "Solution.h"
#include <cstring>
#include <iomanip>
#include <list>
using namespace std;

Solution::Solution(int type, TSP *instance){
    
    this->instance = instance;
    if (type == Solution::basic) create_basic_solution();
    if (type == Solution::greedyA) create_greedy_solution_A();
    if (type == Solution::greedyB) create_greedy_solution_B();
}

void Solution::create_basic_solution(){
    for (int i=0; i<instance->dimension;i++){
        path.push_back(i);
    }
}

void Solution::create_greedy_solution_A(){
    bool visited[instance->dimension];
    memset(visited, 0, sizeof(visited));
    priority_queue<pair<int,int>> aux = instance->nearest[0];
    while(aux.top().second == 0) aux.pop();
    int next = -aux.top().second;
    path.push_back(0);
    visited[0] = true;

    while(true){
        path.push_back(next);
        visited[next] = true;
        aux = instance->nearest[next];
        while (!aux.empty() and visited[-aux.top().second] ){
            aux.pop();
        }
        if (aux.empty()) break;
        next = -aux.top().second; 
    }
}

void Solution::create_greedy_solution_B(){
    bool visited[instance->dimension];
    memset(visited, 0, sizeof(visited));
    priority_queue<pair<int,int>> auxFront = instance->nearest[0];
    priority_queue<pair<int,int>> auxBack = instance->nearest[0];
    
    while(auxFront.top().second == 0) auxFront.pop();
    while(auxBack.top().second == 0) auxBack.pop();
    
    int next = -auxFront.top().second;
    int prev = -auxBack.top().second;
    path.push_back(0);
    visited[0] = true;

    while(true){
        bool haveCicle = false;
        if (next == prev){
            haveCicle = true;
        }
        if (auxFront.top().first >= auxBack.top().first){
            path.push_back(next);
            visited[next] = true;
            auxFront = instance->nearest[next];
            while (!auxFront.empty() and visited[-auxFront.top().second] ){
            auxFront.pop();
            }
            if (auxFront.empty()) break;
            next = -auxFront.top().second;
            if (haveCicle){
                while (!auxBack.empty() and visited[-auxBack.top().second] ){
                auxBack.pop();
                }
                if (auxBack.empty()) break;
                prev = -auxBack.top().second;
            }
        }
        else{
            path.push_front(prev);
            visited[prev] = true;
            auxBack = instance->nearest[prev];
            while (!auxBack.empty() and visited[-auxBack.top().second] ){
            auxBack.pop();
            }
            if (auxBack.empty()) break;
            prev = -auxBack.top().second;
            if (haveCicle){
                while (!auxFront.empty() and visited[-auxFront.top().second] ){
                auxFront.pop();
                }
                if (auxFront.empty()) break;
                next = -auxFront.top().second;
            }
        }
    }

    while(*path.begin() != 0){
        path.push_back(*path.begin());
        path.pop_front();
    }
}

int Solution::get_value(){
    double value = 0;
    int value_to_colect[instance->dimension];
    memset(value_to_colect, 0, sizeof(value_to_colect));
    auto it = path.begin();
    do {
        value_to_colect[instance->deliveries[*it].first] += instance->deliveries[*it].second;
        int from = *it;
        it++;
        if (it == path.end()) it = path.begin();
        int to = *it;
        value += instance->dist[make_pair(from, to)];
        value -= value_to_colect[to];
    }while(it != path.begin());
    return value;
}

Solution* Solution::get_solution(){
    return this;
}

vector<Solution> Solution::get_neighbors(){
    vector<Solution> neighbors;
    Solution aux = *this;
    neighbors.push_back(aux);
    for (auto it1 = aux.path.begin(); it1!=aux.path.end(); ++it1){   
        for (auto it2 = it1; it2!=aux.path.end();){
            aux = *this;
            if (it1 == it2){
                it2++;
                continue;
            } 
            list<int> subPath;
            auto prev = it1;
            auto it1orig = it1;
            prev--;
            it1orig--;
            subPath.splice(subPath.begin(),aux.path,it1, ++it2);
            subPath.reverse();
            prev++;
            aux.path.splice(prev, subPath);
            it1orig++;
            it1 = it1orig;
            neighbors.push_back(aux);
        }
    }
    for (auto it = neighbors.begin(); it!= neighbors.end(); it++){
        while(*it->path.begin() != 0){
                it->path.push_back(*it->path.begin());
                it->path.pop_front();
            }
    }
    return neighbors;
}