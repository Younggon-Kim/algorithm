//https://www.acmicpc.net/problem/12850
#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000007LL
#define BUILDINGS 8
typedef vector<vector<ll>> matrix;

matrix campus = {
   //0, 1, 2, 3, 4, 5, 6, 7
    {0, 1, 1, 0, 0, 0, 0, 0}, //0
    {1, 0, 1, 1, 0, 0, 0, 0}, //1
    {1, 1, 0, 1, 1, 0, 0, 0}, //2
    {0, 1, 1, 0, 1, 1, 0, 0}, //3
    {0, 0, 1, 1, 0, 1, 0, 1}, //4
    {0, 0, 0, 1, 1, 0, 1, 0}, //5
    {0, 0, 0, 0, 0, 1, 0, 1}, //6
    {0, 0, 0, 0, 1, 0, 1, 0}  //7
};

matrix multiply(const matrix &mtx1, const matrix &mtx2) {
    matrix result(BUILDINGS, vector<ll>(BUILDINGS));

    for(int i = 0; i < BUILDINGS; i++) {
        for(int j = 0; j < BUILDINGS; j++) {
            ll cnt = 0;
            for(int k = 0; k < BUILDINGS; k++) {
                cnt += (mtx1[i][k] * mtx2[k][j]) % MOD;
            }
            result[i][j] = cnt % MOD;
        }
    }

    return result;
}

void solve() {
    int d;
    scanf("%d", &d);

    //정답 행렬을 단위 행렬로 초기화
    matrix ans(BUILDINGS, vector<ll>(BUILDINGS));
    for(int i = 0; i < BUILDINGS; i++) {
        ans[i][i] = 1;
    }

    //campus 행렬을 D번 곱하는 방법
    //campus 를 D번 곱하는게 아니라, campus 행렬을 거듭 제곱함으로써 D 를 2로 나누게 된다.
    //e.g. X^4 = X * X * X * X ==> 이렇게 4번 곱하는게 아니라
    //     X^4 = X^2 * X^2     ==> X^2 계산한걸 다시 곱하면, 곱셈은 2번만 하면 된다.
    while(d) {
        if(d & 1) { // D가 홀수라면, campus 행렬을 곱한다
            ans = multiply(ans, campus);
        }
        campus = multiply(campus, campus); //campus 행렬을 제곱한다 => 거듭제곱
        d = d >> 1; //D = D / 2
    }

    printf("%lld\n", ans[0][0]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    solve();
}