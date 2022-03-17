#ifndef Solution_H
#define Solution_H
#include <iostream>
#include <list>
#include "../TSP/TSP.h"
using namespace std;

class Solution{
    private:
    list<int> path;
    int size;
    void create_basic_solution();
    void create_greedy_solution_A();
    void create_greedy_solution_B();
    TSP *instance;

    public:
    const static int basic = 0;
    const static int greedyA = 1;
    const static int greedyB = 2;

    Solution(int type, TSP *instance);
    int get_value();
    Solution* get_solution();
    vector<Solution> get_neighbors();

    friend class TSP;
};

#endif