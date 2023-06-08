//https://www.acmicpc.net/problem/1081
#include <iostream>

using namespace std;

#define MAX_PLACE 10

long long tens[11] = {1}; //자리수 10^0 ~ 10^10 까지 캐싱. 문제에서 숫자가 최대 2*10^9 이므로

/*
 * n : 원본 숫자. e.g. 12345
 * place : 자리수. e.g. 2 는 10^2 를 의미
 * digit : 카운팅 하려는 숫자 1개. e.g. 300 에서 3
*/
long long get_digit_count(long long n, int place, int digit) {
    long long count = 0;

    //1) 현재 자리수 보다 높은 자리수(place + 1) 카운팅
    //e.g. 12345 에서 300 의 3 은 300, 1300, 2300, ... 9300, 10300, 11300, 12300 범위에서 카운팅됨
    //e.g. 300 의 place = 2, digit = 3
    count += n / tens[place + 1] * tens[place]; //300 ~ 12300, 즉 12번이 tens[place] = (10^2) 만큼 카운팅

    //2) 원본 숫자에서 현재 자리수 숫자만 가져오기
    int single_n = n / tens[place] % 10;
    //3) 현재 자리수(place) 의 숫자의 카운팅
    if(single_n > digit) { //e.g. n = 12345, place = 2, digit = 1, single_n = 3
        count += tens[place]; //10^place 만큼만 카운팅 더해줌
    } else if(single_n == digit) { //e.g. n = 12345, place = 2, digit = 3, single_n = 3
        count += (n % tens[place]) + 1; //e.g. 45 + 1 만 카운팅. +1 의 의미는 12300도 카운팅해야 하므로
    }

    return count;
}

long long get_digit_sum(long long n) {
    long long sum = 0;

    //자리수 10^0 ~ 10^9 까지. 문제에서 숫자가 최대 2*10^9 이므로
    for(int place = 0; place < MAX_PLACE; place++) {
        //각 자리에서 숫자 1 ~ 9 를 각각 카운팅. 0은 어차피 더해도 0이므로 카운팅하지 않음
        for(int digit = 1; digit <= 9; digit++) { 
            sum += get_digit_count(n, place, digit) * digit;
        }
    }

    return sum;
}

void solve() {
    long long a, b; //a <= b
    scanf("%lld %lld", &a, &b);

    //10^0 ~ 10^10 초기화
    for(int i = 1; i <= MAX_PLACE; i++) {
        tens[i] = tens[i - 1] * 10;
    }

    printf("%lld\n", get_digit_sum(b) - (a == 0 ? 0 : get_digit_sum(a - 1)));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    solve();
}