#include "LocalSearch.h"
using namespace std;

LocalSearch::LocalSearch(TSP *instance){
    Solution initial(Solution::greedyB, instance);
    bestValue = initial.get_value();
    bestSolution = initial.get_solution();
    getLocal();
}

void LocalSearch::getLocal(){
    
    vector<Solution> neighbors = bestSolution->get_neighbors();
    
    bool hasImprovement = false;
    
    for (int i=0; i<neighbors.size(); i++){
        int value = neighbors[i].get_value();
        if (value < bestValue){
            bestValue = value;
            bestSolution = neighbors[i].get_solution();
            hasImprovement = true;
            cout << bestValue << endl;
        }
    }
    if (hasImprovement) getLocal();
}

int LocalSearch::get_value(){
    return bestValue;
}