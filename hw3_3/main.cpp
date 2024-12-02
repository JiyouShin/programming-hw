#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

#include "functions.hpp"

using namespace std;


int main(){

    vector<vector<int>> my_route;
    my_route.push_back(vector<int>({1,4,5}));
    my_route.push_back(vector<int>({1,2,4}));
    my_route.push_back(vector<int>({2,4,5}));
    my_route.push_back(vector<int>({1,3,2}));
    my_route.push_back(vector<int>({3,4,3}));
    my_route.push_back(vector<int>({1,2,0}));
    my_route.push_back(vector<int>({2,3,1}));
    my_route.push_back(vector<int>({3,4,2}));
    my_route.push_back(vector<int>({1,4,3}));

    flightRoute(4, my_route.size(), my_route);

    return 0;
}

