//https://www.acmicpc.net/problem/1033
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int val = 1;
    vector<int> edges;
}nodes[10];

int get_gcd(int a, int b) {
    if(a == 0) {
        return b;
    }
    return get_gcd(b % a, a);
}

void dfs(int cur, int val, vector<bool> &visited) {
    visited[cur] = true;
    nodes[cur].val *= val;

    for(auto adj : nodes[cur].edges) {
        if(!visited[adj]) {
            dfs(adj, val, visited);
        }
    }
}

void solve() {
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n - 1; i++) {
        int a, b, p, q;
        scanf("%d %d %d %d", &a, &b, &p, &q);

        int gcd_val = get_gcd(nodes[a].val, nodes[b].val);
        int a_mod = nodes[b].val / gcd_val * p;
        int b_mod = nodes[a].val / gcd_val * q;
        int gcd_mod = get_gcd(a_mod, b_mod);

        vector<bool> visited(10, false);
        dfs(a, a_mod / gcd_mod, visited);
        dfs(b, b_mod / gcd_mod, visited);

        nodes[a].edges.push_back(b);
        nodes[b].edges.push_back(a);
    }

    for(int i = 0; i < n; i++) {
        printf("%d ", nodes[i].val);
    }
    printf("\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
}