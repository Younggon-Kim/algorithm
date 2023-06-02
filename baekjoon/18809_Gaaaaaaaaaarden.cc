//https://www.acmicpc.net/problem/18809
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <utility>

using namespace std;

#define MAX_GARDEN_SIZE 50
#define MAX_LIQUID_SIZE 10
const int WATER = 0;
const int WILD_LAND = 1;
const int FERTILE_LAND = 2;

const int NOT_VISIT_COLOR = -1;
const int GREEN_COLOR = 0;
const int RED_COLOR = 1;
const int FLOWER_COLOR = 3;

int garden[MAX_GARDEN_SIZE][MAX_GARDEN_SIZE];
int N, M, G, R;
int ans;
vector<pair<int, int>> fertile_lands; //position(r, c)
bool liquid_visit[MAX_LIQUID_SIZE];
vector<int> green;
vector<int> red;

struct cell {
    int color;
    int time;
} cells[MAX_GARDEN_SIZE][MAX_GARDEN_SIZE];

int dr[] = {-1, 1, 0, 0}; //up, down, left, right
int dc[] = {0, 0, -1, 1}; //up, down, left, right


int bfs() {
    int res = 0;
    memset(cells, -1, sizeof(cells));

    queue<pair<int, int>> q;

    for(int g : green) {
        int r = fertile_lands[g].first;
        int c = fertile_lands[g].second;

        cells[r][c] = {GREEN_COLOR, 0}; //color, time
        q.push({r, c});
    }

    for(int _red : red) {
        int r = fertile_lands[_red].first;
        int c = fertile_lands[_red].second;

        cells[r][c] = {RED_COLOR, 0}; //color, time
        q.push({r, c});
    }

    while(!q.empty()) {
        int curr_r = q.front().first;
        int curr_c = q.front().second;
        q.pop();
        int curr_color = cells[curr_r][curr_c].color;
        int curr_time = cells[curr_r][curr_c].time;

        if(cells[curr_r][curr_c].color == FLOWER_COLOR) continue;

        for(int i = 0; i < 4; i++) { //4 directions
            int next_r = curr_r + dr[i];
            int next_c = curr_c + dc[i];

            if(next_r < 0 || next_r >= N || next_c < 0 || next_c >= M) continue;
            if(garden[next_r][next_c] == WATER) continue;

            if(cells[next_r][next_c].color == NOT_VISIT_COLOR) {
                cells[next_r][next_c].color = curr_color;
                cells[next_r][next_c].time = curr_time + 1;
                q.push({next_r, next_c});
            } else if(cells[next_r][next_c].color != FLOWER_COLOR) {
                if(cells[next_r][next_c].color != curr_color && cells[next_r][next_c].time == curr_time + 1) {
                    cells[next_r][next_c].color = FLOWER_COLOR;
                    res++;
                }
            }
        }
    }

    return res;
}

void dfs(int idx, int cnt, int g, int r) {
    if(cnt > fertile_lands.size()) return;
    if(g > G) return;
    if(R > R) return;
    if(g == G && r == R) {
        ans = max(ans, bfs());
    }

    for(int i = idx; i < fertile_lands.size(); i++) {
        if(liquid_visit[i]) continue;

        liquid_visit[i] = true;
        green.push_back(i);
        dfs(i, cnt + 1, g + 1, r);
        green.pop_back();

        red.push_back(i);
        dfs(i, cnt + 1, g, r + 1);
        red.pop_back();
        liquid_visit[i] = false;
    }
}

void solve() {
    scanf("%d %d %d %d", &N, &M, &G, &R);

    for(int r = 0; r < N; r++) {
        for(int c = 0; c < M; c++) {
            scanf("%d ", &garden[r][c]);

            if(garden[r][c] == FERTILE_LAND) {
                fertile_lands.push_back({r, c});
            }
        }
    }
    dfs(0, 0, 0, 0);
    printf("%d\n", ans);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
}