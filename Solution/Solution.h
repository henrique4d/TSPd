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
    TSP *instance;

    public:
    const static int basic = 0;
    const static int greedyA = 1;

    Solution(int type, int size, TSP *instance);
    int get_value();

    friend class TSP;
};

#endif