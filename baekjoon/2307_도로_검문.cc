//https://www.acmicpc.net/problem/2307
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <climits>
#include <utility>
#include <stack>

using namespace std;

#define NODE_MAX 1000
typedef pair<int, int> pii;

int n, m;
int matrix[NODE_MAX + 1][NODE_MAX + 1]; //인접행렬
int parent[NODE_MAX + 1]; //부모 노드 기록

int dijkstra(int start, int end) {
    vector<bool> visit(n + 1, false);
    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq; //weight, node

    pq.push({0, start});
    dist[start] = 0;

    while(!pq.empty()) {
        int now = std::get<1>(pq.top());
        pq.pop();

        if(visit[now]) continue;
        visit[now] = true;

        for(int adj = 0; adj < n; adj++) {
            if(adj == now) continue; //skip itself
            if(visit[adj]) continue; //skip already visited

            int weight = matrix[now][adj];
            if(weight == 0) continue; //no path

            if(dist[adj] > dist[now] + weight) {
                dist[adj] = dist[now] + weight;
                pq.push({dist[adj], adj});
                parent[adj] = now;
            }
        }
    }

    return dist[end];
}

void solve() {
    int no_block_dist = dijkstra(0, n - 1);

    //find no block path
    stack<int> st;
    for(int i = n - 1; i != 0; i = parent[i]) {
        st.push(i);
    }
    vector<pii> no_block_path;
    int from = 0;
    int to;
    while(!st.empty()) {
        to = st.top();
        st.pop();
        no_block_path.push_back({from, to});
        from = to;
    }

    int diff = 0;

    for(int i = 0; i < no_block_path.size(); i++) {
        int s = no_block_path[i].first;
        int e = no_block_path[i].second;
        int w = matrix[s][e];

        //remove weight on the edge
        matrix[s][e] = matrix[e][s] = 0;
        //find minimum dist
        int dist = dijkstra(0, n - 1);
        //recover removed weight on the edge
        matrix[s][e] = matrix[e][s] = w;

        if(dist == INT_MAX) { //cannot reach end node
            printf("-1\n");
            return;
        }

        diff = max(diff, dist - no_block_dist);
    }
    printf("%d\n", diff);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    memset(matrix, 0, sizeof(matrix));
    memset(parent, 0, sizeof(parent));

    scanf("%d %d", &n, &m);

    for(int i = 0; i < m; i++) {
        int from, to, time;
        scanf("%d %d %d", &from, &to, &time);
        matrix[from - 1][to - 1] = matrix[to - 1][from - 1] = time;
    }

    solve();
}
