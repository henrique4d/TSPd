#ifndef TSP_H
#define TSP_H
#include <map>
#include <utility>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class TSP
{
private:
    map<pair<int, int>, double> dist;

    int dimension;
    int k, j;
    vector<pair<int,int>> deliveries;
    vector<priority_queue<pair<int,int>>> nearest;

    void create_by_lower_diag_row(vector<double> &edge_weight_section);
    void create_by_upper_row(vector<double> &edge_weight_section);
    void create_by_euc_2d(vector<pair<int,int>> &node_coord_section);
    void create_deliveries(int k, int j);
    /* data */

public:
    TSP(int dimension, string edge_weight_type, string edge_weight_format, vector<double> &edge_weight_section,int k, int v);
    TSP(int dimension, string edge_weight_format, vector<pair<int,int>> &node_coord_section,int k, int v);
    
    double get_value();

    friend class Solution;
};

#endif