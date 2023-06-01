//https://www.acmicpc.net/problem/16991
#include <iostream>
#include <cstdio>
#include <cmath>
#include <limits.h>
#include <cstring>

using namespace std;

#define CITY 16

int n;
int pos[CITY][2] = {0};
double graph[CITY][CITY];
double dp[1 << CITY][CITY] = {0};

double tsp(int visit, int now) {
    //now 도시 방문 추가
    visit |= (1 << now);

    //모든 도시를 지난 경우
    if(visit == (1 << n) - 1) {
        //now -> 출발도시(0)으로 가는 경로 있어야 정답 가능
        if(graph[now][0] > 0.0f) {
            return graph[now][0]; //여행 비용 반환
        }
        return __DBL_MAX__;
    }

    double &ret = dp[visit][now];
    //memoziation
    if(ret > 0) {
        return ret;
    }

    ret = __DBL_MAX__;
    for(int i = 0; i < n; i++) {
        // now -> i번 도시로 아직 방문하지 않은 경로가 있는 경우
        if(i != now && (visit & (1 << i)) == 0 && graph[now][i] > 0.0f) {
            //최소 비용 갱신
            ret = min(ret, tsp(visit, i) + graph[now][i]);
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    memset(graph, 0, sizeof(graph));
    memset(dp, 0, sizeof(dp));

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &pos[i][0], &pos[i][1]);
    }

    //make graph
    for(int i = 0; i < n; i++) { //from
        for(int j = 0; j < n; j++) { //to
            if(i == j) continue; //skip itself
            double dist = sqrt(pow(pos[j][0] - pos[i][0], 2) + pow(pos[j][1] - pos[i][1], 2));
            graph[i][j] = dist;
            graph[j][i] = dist;
        }
    }

    double ans = tsp(0, 0);
    if(ans == __DBL_MAX__) {
        printf("Not found\n");
    } else {
        printf("%lf\n", ans);
    }
}