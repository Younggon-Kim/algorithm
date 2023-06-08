# https://www.acmicpc.net/problem/1081
import sys

tens = [1]


def get_digit_count(n: int, place: int, digit: int) -> int:
    count = 0

    # python 은 나눗셈 결과가 실수형으로 계산되는 것에 주의할 것
    count += int(n / tens[place + 1]) * tens[place]
    single_n = int(n / tens[place]) % 10

    if single_n > digit:
        count += tens[place]
    elif single_n == digit:
        count += (n % tens[place]) + 1

    return count


def get_digit_sum(n: int) -> int:
    sum = 0

    for place in range(10):
        for digit in range(1, 10):
            sum += get_digit_count(n, place, digit) * digit

    return sum


def solve():
    a, b = map(int, sys.stdin.readline().strip().split())

    for i in range(11):
        tens.append(tens[-1] * 10)

    print(get_digit_sum(b) - (get_digit_sum(a - 1) if a != 0 else 0))


solve()
