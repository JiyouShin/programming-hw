#include <iostream>
#include <vector>
#include <algorithm>

#include "functions.hpp"

using namespace std;

int main(){

    int n = 3,  sum = 4;
    vector<int> coins = {3,2,1};
    

    std::cout << coinCombinations(n, sum, coins) << std::endl;
    
    return 0;
}

