//https://www.acmicpc.net/problem/20005
#include <iostream>
#include <queue>
#include <cctype>
#include <cstdio>

using namespace std;

const char BOSS = 'B';
const char WALL = 'X';
const char EMPTY = '.';
const int MAX_PLAYERS = 'z' - 'a' + 1;

const int dr[] = {-1, 1, 0, 0}; //up, down, left, right
const int dc[] = {0, 0, -1, 1}; //up, down, left, right

char board[1000][1000];
int M, N, P, BOSS_HP;
int boss_r, boss_c;
int dps[MAX_PLAYERS];

struct Pos {
    int r, c;
};

void get_input() {
    scanf("%d %d %d", &M, &N, &P);
    for(int r = 0; r < M; r++) {
        for(int c = 0; c < N; c++) {
            scanf(" %c", &board[r][c]);
            if(board[r][c] == BOSS) {
                boss_r = r;
                boss_c = c;
            }
        }
    }

    for(int i = 0; i < P; i++) {
        char player;
        scanf(" %c", &player);
        scanf("%d", &dps[player - 'a']);
    }
    scanf("%d", &BOSS_HP);
}

void solve() {
    queue<Pos> q;
    q.push({boss_r, boss_c});

    bool visit[1000][1000] = {false,};
    visit[boss_r][boss_c] = true;

    int arrived_cnt = 0;
    bool arrived[MAX_PLAYERS] = {false,};

    while(BOSS_HP > 0) {
        int sz = q.size();
        for(int i = 0; i < sz; i++) {
            Pos p = q.front();
            q.pop();

            if(islower(board[p.r][p.c])) {
                arrived[board[p.r][p.c] - 'a'] = true;
                ++arrived_cnt;
            }

            for(int j = 0; j < 4; j++) {
                int nr = p.r + dr[j];
                int nc = p.c + dc[j];
                if(nr < 0 || nr >= M || nc < 0 || nc >= N) continue;
                if(board[nr][nc] == WALL) continue;
                if(visit[nr][nc]) continue;

                q.push({nr, nc});
                visit[nr][nc] = true;
            }
        }

        for(int i = 0; i < MAX_PLAYERS; i++) {
            if(arrived[i]) {
                BOSS_HP -= dps[i];
            }
        }
    }

    printf("%d\n", arrived_cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    get_input();
    solve();
}