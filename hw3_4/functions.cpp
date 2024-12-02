#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#include "functions.hpp"

using namespace std;

long coinCombinations(int n, int sum, vector<int> & coins)
{
    vector<long> dp(sum+1, 0);
    dp[0] = 1;
    for (int i = 1; i  <= sum; i++) {
        for (int coin : coins) {
            if (i >= coin) {
                dp[i] = (dp[i] + dp[i - coin]) % INT_MAX;
            }
        }
    }
    return dp[sum];
}