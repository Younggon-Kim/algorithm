//https://www.acmicpc.net/problem/23847
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int TOTAL_STICKS = 6;
string sticks[TOTAL_STICKS] = {"IN", "NU", "UI", "II", "NN", "UU"};

void solve() {
    int n;
    scanf("%d", &n);
    int lens[TOTAL_STICKS] = {0,};

    while(n--) {
        string s; int len;
        cin >> s >> len;
        string revs = s;
        reverse(revs.begin(), revs.end());
        for(int i = 0; i < TOTAL_STICKS; i++) {
            if(s == sticks[i] || revs == sticks[i]) {
                lens[i] += len;
            }
        }
    }

    // IN, NU, UI 모두 없다면
    if(!lens[0] && !lens[1] && !lens[2]) {
        // II, NN, UU 각각을 이어 붙인 것 중에 최대값
        printf("%d\n", max({lens[3], lens[4], lens[5]}));
    }
    // IN 만 있고, NU, UI 없는 경우
    else if(lens[0] && !lens[1] && !lens[2]) {
        // IN, II, NN 이어 붙인 것과 UU 만 이어 붙인 것 중에 최대 값
        printf("%d\n", max({lens[0] + lens[3] + lens[4], lens[5]}));
    }
    // NU 만 있고, IN, UI 없는 경우
    else if(lens[1] && !lens[0] && !lens[2]) {
        // NU, NN, UU 이어 붙인 것과 II 만 이어 붙인 것 중에 최대 값
        printf("%d\n", max({lens[1] + lens[4] + lens[5], lens[3]}));
    }
    // UI 만 있고, IN, NU 없는 경우
    else if(lens[2] && !lens[0] && !lens[1]) {
        // UI, II, UU 이어 붙인 것과 NN 만 이어 붙인 것 중에 최대 값
        printf("%d\n", max({lens[2] + lens[3] + lens[5], lens[4]}));
    }
    // IN, NU, UI 모두 있거나, 2종류 이상 있는 경우 => 다 이어 붙일 수 있음
    else {
        printf("%d\n", lens[0] + lens[1] + lens[2] + lens[3] + lens[4] + lens[5]);
    }
}

int main() {
    freopen(getenv("out"), "w", stdout);
    freopen(getenv("in"), "r", stdin);

    solve();
}