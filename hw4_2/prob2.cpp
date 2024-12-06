#include "prob2.hpp"
#include <vector>
#include <queue>

using namespace std;

int findKnownOrderStudents(int n, std::vector<std::pair<int, int> >& comparisons) {
    // matrix 선언과 동시에 0으로 초기화
    vector<vector<int> > graph(n+1, vector<int>(n+1, 0));

    // input edge loop돌면서 연결되어있는거 1로 update
    for (auto c : comparisons) {
        graph[c.first][c.second] = 1;
    }

    // Floyd-Warshall Algorithm
    for (int k=1; k<=n; k++) {
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                if (graph[i][k] == 1 && graph[k][j] == 1) {
                    graph[i][j] = 1;
                }
            }
        }
    }
    
    // cycle check with topological sort and DAG
    // vertex들의 진입차원을 담을 vector 선언
    vector<int> indegree(n+1, 0);

    // queue 선언
    // graph matrix돌면서 진입차원 계산해주기
    queue<int> q;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<n; j++) {
            if (graph[i][j] == 1) {
                indegree[j]++;
            }
        }
    }

    // 진입차원이 0인 vertex들 queue에 넣어주기
    for (int i=1; i<=n; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }

    // q로 while문 돌면서 indegree 0인 vertex들 sorting    
    int procressedNodeCnt = 0;
    while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        procressedNodeCnt++;

        for (int j=1; j<=n; j++) {
            if (graph[vertex][j] ==1 ) {
                indegree[j]--;
                if (indegree[j] == 0) {
                    q.push(j);
                }
            }
        }
    }

    if (procressedNodeCnt != n) {
        return 0;
    }

    // 모든 vertex들과 연결된 vertex의 개수 check
    int result = 0;
    for (int i=1; i<=n; i++) {
        int cnt = 0;
        for (int j=1; j<=n; j++){
            if (i == j) {
                continue;
            } else {
                if (graph[i][j] == 1 || graph[j][i] == 1) {
                    cnt++;
                }
            }
        }
        if (cnt == n-1) {
            result++;
        }
    }

    return result;
}
