//https://www.acmicpc.net/problem/17090
#include <bits/stdc++.h>
#include <cstring>

using namespace std;

const int MAX_R = 500;
const int MAX_C = 500;

const int dr[] = {-1, 1, 0, 0}; //up, down, left, right
const int dc[] = {0, 0, -1, 1}; //up, down, left, right

const int NOT_VISIT = -1;
const int EXITABLE = 1;
const int CYCLE = 0;

char maze[MAX_R + 1][MAX_C + 1];
int dp[MAX_R + 1][MAX_C + 1];

int row, col;

int next_index(char dir) {
    if(dir == 'U') return 0;
    else if(dir == 'D') return 1;
    else if(dir == 'L') return 2;
    else return 3;
}

int dfs(int r, int c) {
    if(r < 0 || r >= row || c < 0 || c >= col) return EXITABLE;
    if(dp[r][c] != NOT_VISIT) return dp[r][c];

    dp[r][c] = CYCLE;

    int idx = next_index(maze[r][c]);
    dp[r][c] = dfs(r + dr[idx], c + dc[idx]);

    return dp[r][c];
}

void solve() {
    scanf("%d %d", &row, &col);

    memset(dp, NOT_VISIT, (MAX_R + 1) * (MAX_C + 1) * sizeof(int));

    for(int r = 0; r < row; r++) {
        scanf("%s", maze[r]);
    }

    int cnt = 0;
    for(int r = 0; r < row; r++) {
        for(int c = 0; c < col; c++) {
            cnt += dfs(r, c);
        }
    }

    printf("%d\n", cnt);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
}