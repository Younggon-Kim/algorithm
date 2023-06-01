//https://www.acmicpc.net/problem/27519
#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1000000007;
const long long MAX_N = 100000;

bool is_prime[MAX_N + 1];

vector<int> primes;
vector<long long> dp(MAX_N + 1, 0);

void init() {
    //init is_prime
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= MAX_N; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i * i <= MAX_N; i++) {
        if (is_prime[i]) {
            for (int j = i*i; j <= MAX_N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    //init primes
    for (int i = 2; i <= MAX_N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    //init dp
    dp[0] = 1;
    for (int prime : primes) {
        for (int i = prime; i <= MAX_N; i++) {
            dp[i] = (dp[i] + dp[i - prime]) % MOD;
        }
    }
}

void solve() {
    int n;
    scanf("%d", &n);
    printf("%lld\n", dp[n]);
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