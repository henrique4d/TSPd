#include "Solution.h"
#include <cstring>
#include <iomanip>
using namespace std;

Solution::Solution(int type, int size, TSP *instance){
    
    this->instance = instance;
    if (type == Solution::basic) create_basic_solution();
    if (type == Solution::greedyA) create_greedy_solution_A();
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
        aux = instance->nearest[next];    
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
