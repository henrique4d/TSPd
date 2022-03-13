#include <bits/stdc++.h>
#include "./TSP/TSP.h"
#include "./Solution/Solution.h"
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
    
    int k = 0;
    int v = 0;

    if (edge_weight_type == "EXPLICIT"){
        getline(cin, trash_data, ':');
        cin >> edge_weight_format;
        cin >> trash_data;
        
        vector<double> edge_weight_section;
        string value;
        while (cin >> value){
            if (value == "TWOD_DISPLAY"){
                cin >> trash_data;
                continue;
            }
            if (value == "EOF" or value == "DISPLAY_DATA_SECTION") break;
            edge_weight_section.push_back(stod(value));
        }
        if (value!="DISPLAY_DATA_SECTION" and cin >> k >> v);
        TSP instancia(dimension, edge_weight_type, edge_weight_format, edge_weight_section, k, v);
        Solution A(Solution::greedyA,dimension, &instancia);
        cout << A.get_value() << endl;
    } 
    if (edge_weight_type == "EUC_2D"){
        cin >> trash_data;
        vector<pair<int,int>> node_coord_section(dimension);
        string index;
        while (cin >> index){
            if (index == "EOF") break;
            double x,y;
            cin >> x >> y;
            node_coord_section[stod(index)-1] = make_pair(x,y);
        }
        if (cin >> k >> v);
        TSP instancia(dimension, edge_weight_type, node_coord_section, k, v);
        Solution A(Solution::greedyA, dimension, &instancia);
        cout << A.get_value() << endl;
    }
    return 0;
}