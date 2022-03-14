#include "TSP.h"
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

TSP::TSP(int dimension, string edge_weight_type, string edge_weight_format, vector<double> &edge_weight_section, int k, int v){
    this->dimension = dimension;
    nearest.resize(dimension);
    create_deliveries(k,v);
    if (edge_weight_type == "EXPLICIT" and edge_weight_format == "LOWER_DIAG_ROW" ) create_by_lower_diag_row(edge_weight_section);
    if (edge_weight_type == "EXPLICIT" and edge_weight_format == "UPPER_ROW" ) create_by_upper_row(edge_weight_section);
}

TSP::TSP(int dimension, string edge_weight_type, vector<pair<int,int>> &node_coord_section, int k, int v){    
    this->dimension = dimension;
    nearest.resize(dimension);
    create_deliveries(k,v);
    if (edge_weight_type == "EUC_2D") create_by_euc_2d(node_coord_section);
}

void TSP::create_by_lower_diag_row(vector<double> &edge_weight_section){    
    for (int i=0; i<dimension; i++){
        for (int j=0; j<=i; j++){
            dist[make_pair(i,j)] = edge_weight_section[(i*(i+1)/2) + j];
            dist[make_pair(j,i)] = edge_weight_section[(i*(i+1)/2) + j];
            nearest[i].push(make_pair(-edge_weight_section[(i*(i+1)/2) + j],-j));
            nearest[j].push(make_pair(-edge_weight_section[(i*(i+1)/2) + j],-i)); 
        }
    }
}

void TSP::create_by_upper_row(vector<double> &edge_weight_section){
    for (int i=0; i<dimension; i++){
        for (int j=1; j<dimension-i; j++){
            int position = ((dimension-1)+dimension-i)*i/2 + j - 1;
            dist[make_pair(i,i+j)] = edge_weight_section[position];
            dist[make_pair(i+j,i)] = edge_weight_section[position];
            nearest[i].push(make_pair(-edge_weight_section[position],-(i+j)));
            nearest[i+j].push(make_pair(-edge_weight_section[position],-i));
        }
    }
}

void TSP::create_by_euc_2d(vector<pair<int,int>> &node_coord_section){
    
    for (int i=0; i<dimension-1; i++){
        for (int j=i+1; j<dimension; j++){
            double value = hypot(node_coord_section[i].first - node_coord_section[j].first, node_coord_section[i].second - node_coord_section[j].second);  
            value = (int)(value+0.5);
            dist[make_pair(i,j)] = value;
            dist[make_pair(j,i)] = value;
            nearest[i].push(make_pair(-value, -j));
            nearest[j].push(make_pair(-value, -i));
        }
    }
}

void TSP::create_deliveries(int k, int v){
    deliveries.resize(dimension, make_pair(0,0));
    for (int i=0; i<k; i++){
        if (2*(i+1) < dimension) deliveries[2*i+1] = make_pair(2*(i+1), v);
    }
}

double TSP::get_value(){
    double value = 0;
    int value_to_colect[dimension];
    memset(value_to_colect, 0, sizeof(value_to_colect));
    for (int i=0; i<dimension-1; i++){
        value_to_colect[deliveries[i].first] += deliveries[i].second;
        value += dist[make_pair(i,i+1)];
        value -= value_to_colect[i];
    }
    value += dist[make_pair(dimension-1, 0)];
    return value;
}