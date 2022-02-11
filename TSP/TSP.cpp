#include "TSP.h"
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

TSP::TSP(int dimension, string edge_weight_type, string edge_weight_format, vector<double> &edge_weight_section){
    this->dimension = dimension;
    if (edge_weight_format == "LOWER_DIAG_ROW" ) create_by_lower_diag_row(edge_weight_section);
}

void TSP::create_by_lower_diag_row(vector<double> &edge_weight_section){
    for (int i=0; i<dimension; i++){
        for (int j=0; j<=i; j++){
            dist[make_pair(i,j)] = edge_weight_section[(i*(i+1)/2) + j];
            dist[make_pair(j,i)] = edge_weight_section[(i*(i+1)/2) + j];
        }
    }
}

double TSP::get_value(){
    double value = 0;
    for (int i=0; i<dimension-1; i++){
        value += dist[make_pair(i,i+1)];
    }
    value += dist[make_pair(dimension-1, 0)];

    cout << value << endl;
    return value;
}