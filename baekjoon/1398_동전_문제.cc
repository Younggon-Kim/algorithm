//https://www.acmicpc.net/problem/1398
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

const int MAX_RANGE = 100;
int dp[MAX_RANGE];
int coins[3] = {1, 10, 25};

int init_dp(int val) {
    if(val == 0) return 0; //base case
    if(dp[val] != -1) return dp[val];

    for(int i = 0; i < 3; i++) {
        int rest = val - coins[i]; //1, 10, 25 를 빼고 남은 금액
        if(rest < 0) continue; //음수이면 동전 금액을 뺀게 잘못된 경우

        if(dp[val] == -1) { //초기화되지 않았다면
            dp[val] = init_dp(val - coins[i]) + 1; //1, 10, 25 를 뺀 금액에서의 개수 + 1 로 초기화
        } else {
            dp[val] = min(dp[val], init_dp(val - coins[i]) + 1); //1, 10, 25 를 뺀 금액에서의 개수 + 1 과 현재 개수 중 최소값 선택
        }
    }
    return dp[val]; //현재금액(val) 을 만들 수 있는 최소 동전 개수 반환
}

void init() {
    memset(dp, -1, sizeof(dp));

    dp[0] = 0; //0 일때 0으로 반드시 초기화해야 함 => 숫자를 2자리씩 잘랐을 때, 00 혹은 0 인 경우 동전 개수는 0 으로 반환해야 하므로
    for(int i = 99; i > 0; i--) {
        init_dp(i); //1 ~ 99 까지 초기화
    }
}

void solve() {
    char temp[20];
    scanf("%s", temp);
    string s(temp);

    int ans = 0;
    for(int i = s.length() - 1; i >= 0; i -= 2) { //1의 자리부터. 눈으로 봤을 때 맨 오른쪽 부터 2자리씩 잘라서 계산
        int idx = i;
        int len = 2;
        if(i == 0) { //가장 왼쪽 숫자에 도착했을 때
            if(s.length() % 2 != 0) { //마지막에 숫자 개수가 홀수 일때
                len = 1;
            }
        } else { //가장 왼쪽 도착하기 전에 기본적으로 2자리씩 잘라지는 경우
            idx = i - 1; //2자리를 잘라야하므로, i - 1 부터 2개를 substr 해야함
        }
        int n = stoi(s.substr(idx, len));
        ans += dp[n];
    }
    printf("%d\n", ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();

    int tc;
    scanf("%d", &tc);

    while(tc--) {
        solve();
    }
}