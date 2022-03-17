#ifndef LocalSearch_H
#define LocalSearch_H
#include "../Solution/Solution.h"
#include "../TSP/TSP.h"

using namespace std;

class LocalSearch{
    private:
    int bestValue;
    Solution *bestSolution;
    void getLocal();
    public:
    LocalSearch(TSP *instance);
    int get_value();
};

#endif