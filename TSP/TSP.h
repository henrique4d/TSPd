#ifndef TSP_H
#define TSP_H
#include <map>
#include <utility>
#include <iostream>
#include <vector>
using namespace std;
class TSP
{
private:
    map<pair<int, int>, double> dist;
    int dimension;

    void create_by_lower_diag_row(vector<double> &edge_weight_section);
    void create_by_upper_row(vector<double> &edge_weight_section);
    void create_by_euc_2d(vector<pair<int,int>> &node_coord_section);
    /* data */

public:
    TSP(int dimension, string edge_weight_type, string edge_weight_format, vector<double> &edge_weight_section);
    TSP(int dimension, string edge_weight_format, vector<pair<int,int>> &node_coord_section);
    
    double get_value();
};

#endif