#include <vector>
#include <iostream>
#include <climits>
#include <utility> 
#include <map>

using namespace std;

/*//////////////////////// Description ////////////////////////////
There are n cities in a logistics network, numbered from 0 to n−1. 

The edges array represents the logistics routes between cities and the corresponding transportation costs. 

Specifically, edges[i] = [from_i, to_i, weight_i] indicates a bidirectional logistics route between city from_i and city to_i, 
with a transportation cost of weight_i.

When considering each city as a potential logistics hub, 
calculate the number of cities reachable from the hub with a maximum transportation cost of distanceThreshold. 

Identify the city (hub) that can reach the most number of cities. 
If there are multiple such cities, return the city with the largest numerical index.

Constraints:
    2 <= n <= 100
    1 <= edges.length <= n * (n - 1) / 2
    edges[i].length == 3
    0 <= fromi < toi < n
    1 <= weighti, distanceThreshold <= 10^4
    All pairs (fromi, toi) are distinct.
////////////////////////////////////////////////////////////////*/

class Solution {
public:
    /* ///////////////////////////////////// TODO 1 ///////////////////////////////////////
    This function uses the Floyd-Warshall algorithm to compute the shortest paths 
    between all pairs of cities and determine the city that meets the problem's conditions.
    ////////////////////////////////////////////////////////////////////////////////////*/
    int floydWarshall (int n, std::vector<std::vector<int>>& edges, int distanceThreshold) {
        vector<vector<int> > graph(n, vector<int>(n, 1000001));
        // i랑 j같을 때 0으로 초기화하기
        for (int i=0; i<=n-1; i++) {
            for (int j=0; j<=n-1; j++) {
                if (i == j) { graph[i][j] = 0; }
            }
        }
        // undirected라서 양방으로 weight 채우기
        for (const auto& edge : edges) {
            graph[edge[0]][edge[1]] = edge[2];
            graph[edge[1]][edge[0]] = edge[2];
        }

        // 그 다음에 min값 update
        // Floyd-Warshall Algorithm
        for (int k=0; k<=n-1; k++) {
            for (int i=0; i<=n-1; i++) {
                for (int j=0; j<=n-1; j++) {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }

        // 각 vertex별로 distanceThreshold보다 작은 path count
        vector<int> resultVec(n, 0);
        for (int i = 0; i <= n-1; i++) {
            int cnt = 0;
            for (int j = 0; j<=n-1; j++) {
                if (graph[i][j] <= distanceThreshold && i != j) {
                    cnt++;
                }
            }
            resultVec[i] = cnt;
        }

        // 최댓값 찾기
        // tie값이 생길 때 더 큰 city를 return하니깐 큰 수부터 역순으로 loop
        int cityResult = -1;
        int countResult = 0;
        for (int i =n-1; i>=0; i--) {
            if (countResult < resultVec[i]) {
                cityResult = i;
                countResult = resultVec[i];
            } else if (countResult == resultVec[i]) {
                if (cityResult < i) {
                    cityResult = i;
                    countResult = resultVec[i];
                } 
            }
        }
        return cityResult;
    }

    /* ///////////////////////////////////// TODO 2 ///////////////////////////////////////
    This function uses the Bellman Ford algorithm to compute the shortest paths 
    between all pairs of cities and determine the city that meets the problem's conditions.
    ////////////////////////////////////////////////////////////////////////////////////*/
    int bellmanFord(int n, std::vector<std::vector<int>>& edges, int distanceThreshold) {
        // bellman-ford algorithm
        vector<vector<int> > bf(n, vector<int>(n, 100001));
        // 모든 vertex를 source로 
        for (int i=0; i<=n-1; i++) {
            bf[i][i] = 0;
            // 전체 vertex-1번만큼 pass돌기
            for (int p=0; p<=n-2; p++) {
                // edges 대해서 loop
                for (const auto& edge : edges) {
                    bf[i][edge[1]] = min(bf[i][edge[1]], bf[i][edge[0]] + edge[2]);
                    bf[i][edge[0]] = min(bf[i][edge[0]], bf[i][edge[1]] + edge[2]);
                }
            }
        }

        // 각 vertex별로 distanceThreshold보다 작은 path count
        vector<int> resultVec(n, 0);
        for (int i = 0; i <= n-1; i++) {
            int cnt = 0;
            for (int j = 0; j<=n-1; j++) {
                if (bf[i][j] <= distanceThreshold && i != j) {
                    cnt++;
                }
            }
            resultVec[i] = cnt;
        }

        // 최댓값 찾기
        // tie값이 생길 때 더 큰 city를 return하니깐 큰 수부터 역순으로 loop
        int cityResult = -1;
        int countResult = 0;
        for (int i =n-1; i>=0; i--) {
            if (countResult < resultVec[i]) {
                cityResult = i;
                countResult = resultVec[i];
            } else if (countResult == resultVec[i]) {
                if (cityResult < i) {
                    cityResult = i;
                    countResult = resultVec[i];
                } 
            }
        }
        return cityResult;
    }
};

int main() {
    Solution solution;

    int n1 = 4;
    std::vector<std::vector<int>> edges1 = {{0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}};
    int distanceThreshold1 = 4;
    std::cout << "Test Case 1 (Floyd Warshall) Output: " << solution.floydWarshall(n1, edges1, distanceThreshold1) << std::endl; // Expected output: 2
    std::cout << "Test Case 1 (Bellman Ford) Output: " << solution.bellmanFord(n1, edges1, distanceThreshold1) << std::endl; // Expected output: 2


    int n2 = 5;
    std::vector<std::vector<int>> edges2 = {{0, 1, 2}, {0, 4, 8}, {1, 2, 3}, {1, 4, 2}, {2, 3, 1}, {3, 4, 1}};
    int distanceThreshold2 = 2;
    std::cout << "Test Case 2 (Floyd Warshall) Output: " << solution.floydWarshall(n2, edges2, distanceThreshold2) << std::endl; // Expected output: 4
    std::cout << "Test Case 2 (Bellman Ford) Output: " << solution.bellmanFord(n2, edges2, distanceThreshold2) << std::endl; // Expected output: 4

    int n3 = 3;
    std::vector<std::vector<int>> edges3 = {{0, 1, 1}, {1, 2, 1}, {0, 2, 2}};
    int distanceThreshold3 = 2;
    std::cout << "Test Case 3 (Floyd Warshall) Output: " << solution.floydWarshall(n3, edges3, distanceThreshold3) << std::endl; // Expected output: 2
    std::cout << "Test Case 3 (Bellman Ford) Output: " << solution.bellmanFord(n3, edges3, distanceThreshold3) << std::endl; // Expected output: 2

    int n4 = 4;
    std::vector<std::vector<int>> edges4 = {{0, 1, 3}, {2, 3, 1}};
    int distanceThreshold4 = 2;
    std::cout << "Test Case 4 (Floyd Warshall) Output: " << solution.floydWarshall(n4, edges4, distanceThreshold4) << std::endl; // Expected output: 3
    std::cout << "Test Case 4 (Bellman Ford) Output: " << solution.bellmanFord(n4, edges4, distanceThreshold4) << std::endl; // Expected output: 3

    int n5 = 1;
    std::vector<std::vector<int>> edges5 = {};
    int distanceThreshold5 = 0;
    std::cout << "Test Case 5 (Floyd Warshall) Output: " << solution.floydWarshall(n5, edges5, distanceThreshold5) << std::endl; // Expected output: 0
    std::cout << "Test Case 5 (Bellman Ford) Output: " << solution.bellmanFord(n5, edges5, distanceThreshold5) << std::endl; // Expected output: 0

    int n6 = 100;
    std::vector<std::vector<int>> edges6 = {
        {0, 1, 10000}, {0, 2, 5000}, {1, 2, 4000}, {2, 3, 7000}, {3, 4, 2000},
        {4, 5, 8000}, {5, 6, 6000}, {6, 7, 9000}, {7, 8, 3000}, {8, 9, 10000}
    };
    int distanceThreshold6 = 20000;
    std::cout << "Test Case 6 (Floyd Warshall) Output: " << solution.floydWarshall(n6, edges6, distanceThreshold6) << std::endl; // Expected output: 5
    std::cout << "Test Case 6 (Bellman Ford) Output: " << solution.bellmanFord(n6, edges6, distanceThreshold6) << std::endl; // Expected output: 5

    int n7 = 50;
    std::vector<std::vector<int>> edges7 = {
        {0, 1, 300}, {1, 2, 200}, {2, 3, 400}, {3, 4, 500}, {4, 5, 300},
        {5, 6, 600}, {6, 7, 700}, {7, 8, 100}, {8, 9, 200}, {9, 10, 500},
        {10, 11, 400}, {11, 12, 300}, {12, 13, 600}, {13, 14, 700}, {14, 15, 200}
    };
    int distanceThreshold7 = 1500;
    std::cout << "Test Case 7 (Floyd Warshall) Output: " << solution.floydWarshall(n7, edges7, distanceThreshold7) << std::endl; // Expected output: 12
    std::cout << "Test Case 7 (Bellman Ford) Output: " << solution.bellmanFord(n7, edges7, distanceThreshold7) << std::endl; // Expected output: 12
    
    return 0;
}
