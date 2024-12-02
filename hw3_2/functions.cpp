#include <iostream> 
#include <queue>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <climits>

#include "functions.hpp"

using namespace std; 

int minDistance(vector<vector<int> >& points) {
    vector<bool> visited(points.size(), false);
    vector<int> minDisVec(points.size(), INT_MAX);

    int distance = 0;
    minDisVec[0] = 0;

    for (int i = 0; i < points.size(); i++) {
        int minDis = INT_MAX;
        int minIdx = -1;

        for (int q = 0; q < points.size(); q++) {
            if (!visited[q] && minDisVec[q] < minDis) {
                minDis = minDisVec[q];
                minIdx = q;
            }
        }

        visited[minIdx] = true;
        distance += minDis;

        for (int j = 0; j < points.size(); j++) {
            if (!visited[j]) {
                int dis = abs(points[minIdx][0] - points[j][0]) + abs(points[minIdx][1] - points[j][1]);
                if (dis < minDisVec[j]) {
                    minDisVec[j] = dis;
                }
            }
        }
    }
    return distance;
}