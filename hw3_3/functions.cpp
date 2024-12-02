#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional>

#include "functions.hpp"

using namespace std;

void flightRoute(const int n, const int m, const vector<vector<int> > & route_info)
{
    vector<vector<pair <int, long long> > > graph(n+1);
    for (const auto route : route_info) {
        graph[route[0]].emplace_back(route[1], route[2]);
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;

    vector<long long> prices(n+1, LONG_MAX);
    vector<long long> routeCounts(n+1, 0);
    vector<int> minimumFlights(n+1, INT_MAX);
    vector<int> maximumFlights(n+1, 0);

    prices[1] = 0; 
    routeCounts[1] = 1;
    minimumFlights[1] = 0;
    maximumFlights[1] = 0;

    pq.push(make_pair(0, 1));

    while (!pq.empty()) {
        long long currCost = pq.top().first;
        int currCity = pq.top().second;
        pq.pop();

        if (currCost > prices[currCity]) continue;

        for (const auto [nextCity, nextCost] : graph[currCity]) {
            long long newCost = currCost + nextCost;
            if (newCost < prices[nextCity]) {
                prices[nextCity] = newCost;
                pq.push(make_pair(newCost, nextCity));
                routeCounts[nextCity] = routeCounts[currCity];
                minimumFlights[nextCity] = minimumFlights[currCity] + 1;
                maximumFlights[nextCity] = maximumFlights[currCity] + 1;
                
            } else if (newCost == prices[nextCity]) {
                routeCounts[nextCity] = (routeCounts[nextCity] + routeCounts[currCity]) % INT_MAX;
                minimumFlights[nextCity] = min(minimumFlights[nextCity], minimumFlights[currCity] + 1);
                maximumFlights[nextCity] = max(maximumFlights[nextCity], maximumFlights[currCity] + 1);
                
            }
        }
    }

    long long minPrice = prices[n];
    long long routeCnt = routeCounts[n] % INT_MAX;
    int minFlightCnt = minimumFlights[n];
    int maxFlightCnt = maximumFlights[n];

    cout << minPrice << " " << routeCnt << " " << minFlightCnt << " " << maxFlightCnt;

    
}