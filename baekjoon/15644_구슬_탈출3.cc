// https://www.acmicpc.net/problem/15644
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

#define FAST_IO ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define READ_TC freopen(getenv("in"), "rt", stdin); freopen(getenv("out"), "wt", stdout); 

#define MAX_BOARD_SZ 10

struct Bead {
    int red_r, red_c, blue_r, blue_c, dir; //dir 은 방향을 나타내는 index 로도 쓰이고, 방향 전환 횟수로도 사용
    //queue 에는 dir 이 방향 전환 횟수로 사용
    //path 에는 dir 이 방향을 나타내는 index 로 사용
};

char board[MAX_BOARD_SZ][MAX_BOARD_SZ];
bool visited[MAX_BOARD_SZ][MAX_BOARD_SZ][MAX_BOARD_SZ][MAX_BOARD_SZ]; //red, blue 위치 방문 기록
Bead path[MAX_BOARD_SZ][MAX_BOARD_SZ][MAX_BOARD_SZ][MAX_BOARD_SZ]; //red, blue 위치에서 경로(이전 위치, 방향) 기록
const char direction[] = {'U', 'D', 'L', 'R'};
const int dr[] = {-1, 1, 0, 0}; //up, down, left, right
const int dc[] = {0, 0, -1, 1}; //up, down, left, right

queue<Bead> q;

//다음 위치가 벽(#)이 아니면서 현재 위치가 구멍(O)이 아닐 때 까지 계속 이동
void move_next(int &r, int &c, int &cnt, int dr, int dc) {
    //입력되는 모든 보드의 가장자리에는 모두 '#'이 있기 때문에
    //r + dr 이나 c + dc 가 board 의 경계를 벗어나지 않음
    while(board[r + dr][c + dc] != '#' && board[r][c] != 'O') {
        r += dr;
        c += dc;
        ++cnt; //위치 이동한 횟수
    }
}

// 빨간 구슬이 구멍에 빠지면 성공이지만, 파란 구슬이 구멍에 빠지면 실패이다.
void solve() {
    while(!q.empty()) {
        int red_r = q.front().red_r, red_c = q.front().red_c;
        int blue_r = q.front().blue_r, blue_c = q.front().blue_c;
        int move_cnt = q.front().dir;
        q.pop();

        if(move_cnt >= 10) break; //방향 전환 횟수가 10이상이면 실패 => BFS 탐색이므로 현재가 최소 방향 전환 횟수를 가지는 탐색이므로 break 해도 됨

        for(int i = 0; i < 4; i++) { //4 directions
            int next_red_r = red_r, next_red_c = red_c, next_blue_r = blue_r, next_blue_c = blue_c;
            int r_cnt = 0, b_cnt = 0;
            move_next(next_red_r, next_red_c, r_cnt, dr[i], dc[i]);
            move_next(next_blue_r, next_blue_c, b_cnt, dr[i], dc[i]);

            if(board[next_blue_r][next_blue_c] == 'O') continue; //blue 의 다음 위치가 구멍(O)이면 실패이므로, 이 경로는 정답이 아님

            if(board[next_red_r][next_red_c] == 'O') { //red 의 다음 위치가 구멍(O)이면 정답
                //정답 방향 전환 경로 찾기 => 현재 위치에서 처음 출발 위치로의 방향 경로 저장 => 나중에 정답은 역순으로 출력
                vector<char> ans_path;
                ans_path.push_back(direction[i]); //현재 위치 저장
                Bead &b = path[red_r][red_c][blue_r][blue_c]; //현재 위치에서 참조할 수 있는 이전 위치 가져오기

                while(b.red_r != 0) { //이전 위치가 유효하다면
                    int prev_red_r = b.red_r, prev_red_c = b.red_c;
                    int prev_blue_r = b.blue_r, prev_blue_c = b.blue_c;
                    ans_path.push_back(direction[b.dir]); //이전 위치를 정답 경로에 저장
                    b = path[prev_red_r][prev_red_c][prev_blue_r][prev_blue_c]; //현재 위치를 이전 위치로 초기화
                }
                printf("%d\n", move_cnt + 1); //정답 방향 전환 횟수 출력
                for(int j = ans_path.size() - 1; j >= 0; j--) { //정답 방향 전환 경로를 역순으로 출력
                    printf("%c", ans_path[j]);
                }
                printf("\n");
                return;
            }
            //red 와 blue 가 같은 위치에 있다면
            if(next_red_r == next_blue_r && next_red_c == next_blue_c) {
                if(r_cnt > b_cnt) { //red 가 더 멀리 있었기 때문에, 카운트 개수가 많음
                    //따라서 red 위치가 blue 보다 뒤에 있어야 함
                    next_red_r -= dr[i];
                    next_red_c -= dc[i];
                } else {
                    //blue 가 red 보다 멀리 있었기 때문에
                    //blue 의 위치를 red 보다 뒤에 두어야 함
                    next_blue_r -= dr[i];
                    next_blue_c -= dc[i];
                }
            }

            //이미 방문한 위치는 skip
            if(visited[next_red_r][next_red_c][next_blue_r][next_blue_c]) continue;
            //방문 기록
            visited[next_red_r][next_red_c][next_blue_r][next_blue_c] = true;
            //다음 위치를 queue 에 저장
            q.push({next_red_r, next_red_c, next_blue_r, next_blue_c, move_cnt + 1}); //여기서 dir 에는 방향 전환 횟수를 기록
            //경로 저장 => 현재 위치를 다음 위치가 참조할 수 있게끔 => child -> parent 느낌
            path[next_red_r][next_red_c][next_blue_r][next_blue_c] = {red_r, red_c, blue_r, blue_c, i}; // 여기서 dir 에는 방향(direction) index 를 기록
        }
    }

    printf("-1\n"); //Not found solution
}

int main() {
    FAST_IO
    READ_TC

    int n, m;
    int red_r, red_c, blue_r, blue_c;

    scanf("%d %d", &n, &m);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%1s", &board[i][j]);
            if(board[i][j] == 'R') red_r = i, red_c = j;
            else if(board[i][j] == 'B') blue_r = i, blue_c = j;
        }
    }

    visited[red_r][red_c][blue_r][blue_c] = true; //red, blue 의 현재 위치를 방문 기록
    q.push({red_r, red_c, blue_r, blue_c, 0}); //red, blue 의 현재 위치를 BFS 탐색을 위해 queue 에 저장
    solve();
}