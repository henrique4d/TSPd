#include <bits/stdc++.h>
#include "./TSP/TSP.h"
using namespace std;

int main (){
    string trash_data;
    getline(cin, trash_data);
    getline(cin, trash_data);
    getline(cin, trash_data);

    int dimension;
    string edge_weight_type;
    string edge_weight_format;

    getline(cin, trash_data, ':');    
    cin >> dimension;

    getline(cin, trash_data, ':');
    cin >> edge_weight_type;
    
    getline(cin, trash_data, ':');
    cin >> edge_weight_format;

    cin >> trash_data;
    
    vector<double> edge_weight_section;
    string value;
    while (cin >> value){
        if (value == "EOF") break;
        edge_weight_section.push_back(stod(value));
    }

    TSP instancia(dimension, edge_weight_type, edge_weight_format, edge_weight_section);

    instancia.get_value();
    return 0;
}