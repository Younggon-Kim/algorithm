#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define MAX_N 1000000LL
bool is_prime[MAX_N + 1];

vector<int> primes;

void init() {
    //init is_prime
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i <= MAX_N; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i <= sqrt(MAX_N); i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX_N; j += i) {
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
}

int main() {
    init();

    //print primes
    for(auto prime: primes) {
        printf("%d\n", prime);
    }
}