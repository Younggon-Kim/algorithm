//https://www.acmicpc.net/problem/17394
#include <iostream>
#include <cmath>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

const int MIN_RANGE = 2;
const int MAX_RANGE = 1000000;
bool is_prime[MAX_RANGE + 1];

void init() {
    fill_n(is_prime, MAX_RANGE + 1, true);
    is_prime[0] = is_prime[1] = false;

    for(int i = 2; i <= sqrt(MAX_RANGE); i++) {
        if(is_prime[i]) {
            for(int j = i * i; j <= MAX_RANGE; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

void solve() {
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);

    int snaps = INT_MAX;

    vector<bool> visit(MAX_RANGE, false);
    queue<pair<int, int>> q; //current N, snaps
    q.push({n, 0});
    visit[n] = true;

    while(!q.empty()) {
        int curr_n = q.front().first;
        int curr_snaps = q.front().second;
        q.pop();

        if(curr_n >= a && curr_n <= b && is_prime[curr_n]) {
            snaps = min(snaps, curr_snaps);
            break;
        }

        int next_nums[] = {curr_n / 3, curr_n / 2, curr_n + 1, curr_n - 1};
        for(int next_n : next_nums) {
            if(!visit[next_n] && next_n >= MIN_RANGE && next_n <= MAX_RANGE) {
                q.push({next_n, curr_snaps + 1});
                visit[next_n] = true;
            }
        }
    }

    printf("%d\n", snaps == INT_MAX ? -1 : snaps);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();

    int tc;
    scanf("%d", &tc);

    while(tc--) {
        solve();
    }
}