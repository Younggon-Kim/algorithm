import sys

n, m = map(int, sys.stdin.readline().strip().split())
board = [sys.stdin.readline().strip() for _ in range(n)]

print(f'{n=}, {m=}')
print(f'{board=}')

# n=5, m=5
# board=['#####', '#..B#', '#.#.#', '#RO.#', '#####']
