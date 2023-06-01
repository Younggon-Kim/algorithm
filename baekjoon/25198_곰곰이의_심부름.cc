//https://www.acmicpc.net/problem/25198
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 100000;
vector<int> graph[MAX_N + 1];

int bfs(int n, int start, int end) {
    vector<bool> visit(n + 1, false);
    queue<pair<int, int>> q;
    visit[start] = true;
    q.push({start, 1});

    while(!q.empty()) {
        int curr = q.front().first;
        int len = q.front().second;
        q.pop();

        if(curr == end) {
            return len;
        }

        for(int adj : graph[curr]) {
            if(visit[adj]) continue;
            visit[adj] = true;
            q.push({adj, len + 1});
        }
    }
    return 0;
}

void solve() {
    int n, s, c, h;
    scanf("%d", &n);
    scanf("%d %d %d", &s, &c, &h);

    for(int i = 0; i < n - 1; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        graph[v1].push_back(v2);
        graph[v2].push_back(v1);
    }

    //SC, CH 경로의 개수
    int len_with_c = bfs(n, s, c) + bfs(n, c, h) - 1; //중간에 심부름 도시가 2번 포함되기 때문에 -1 빼줌
    int len_without_c = bfs(n, s, h); //C를 거치지 않고, SH 로 가는 최단 경로

    //SC, CH 간의 중복된 노드 개수 계산
    long long duplicated = (len_with_c - len_without_c) / 2;
    //중복되지 않은 노드 개수 계산
    long long non_duplicated = len_with_c - duplicated;
    //방문 순서가 역전되는 쌍 = (중복 노드 * (중복 노드 + 1)) / 2
    //방분 순서가 지켜지는 쌍 = (중복 아닌 노드 * (중복 아닌 노드 - 1)) / 2
    long long answer = ((non_duplicated * (non_duplicated - 1)) + (duplicated * (duplicated + 1))) / 2;
    printf("%lld\n", answer);}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
}