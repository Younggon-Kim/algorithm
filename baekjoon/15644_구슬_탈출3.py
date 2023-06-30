import sys

BOARD_SIZE = 10

visited = [[[[False for _ in range(BOARD_SIZE)] for _ in range(BOARD_SIZE)] for _ in range(BOARD_SIZE)] for _ in range(BOARD_SIZE)]
path = [[[[(-1, -1, -1, -1, 0) for _ in range(BOARD_SIZE)] for _ in range(BOARD_SIZE)] for _ in range(BOARD_SIZE)] for _ in range(BOARD_SIZE)]
queue = []
direction = ['U', 'D', 'L', 'R']
dr = [-1, 1, 0, 0]
dc = [0, 0, -1, 1]


def move_next(r: int, c: int, dr: int, dc: int) -> tuple[int, int, int]:
    cnt = 0
    while board[r + dr][c + dc] != '#' and board[r][c] != 'O':
        r += dr
        c += dc
        cnt += 1

    return r, c, cnt


def solve():
    while len(queue) > 0:
        red_r, red_c, blue_r, blue_c, move_cnt = queue.pop(0)

        if move_cnt >= 10:
            break

        for i in range(4):
            next_red_r, next_red_c, red_cnt = move_next(red_r, red_c, dr[i], dc[i])
            next_blue_r, next_blue_c, blue_cnt = move_next(blue_r, blue_c, dr[i], dc[i])

            if board[next_blue_r][next_blue_c] == 'O':  # failure case
                continue

            if board[next_red_r][next_red_c] == 'O':
                ans_path = [direction[i]]

                prev_red_r, prev_red_c, prev_blue_r, prev_blue_c, prev_dir = path[red_r][red_c][blue_r][blue_c]

                while prev_red_r != -1:
                    ans_path.append(direction[prev_dir])
                    prev_red_r, prev_red_c, prev_blue_r, prev_blue_c, prev_dir = path[prev_red_r][prev_red_c][prev_blue_r][prev_blue_c]

                print(f'{move_cnt + 1}')
                print(''.join(ans_path[-1::-1]))
                return

            if next_red_r == next_blue_r and next_red_c == next_blue_c:
                if red_cnt > blue_cnt:
                    next_red_r -= dr[i]
                    next_red_c -= dc[i]
                else:
                    next_blue_r -= dr[i]
                    next_blue_c -= dc[i]

            if visited[next_red_r][next_red_c][next_blue_r][next_blue_c]:
                continue

            visited[next_red_r][next_red_c][next_blue_r][next_blue_c] = True
            queue.append((next_red_r, next_red_c, next_blue_r, next_blue_c, move_cnt + 1))
            path[next_red_r][next_red_c][next_blue_r][next_blue_c] = (red_r, red_c, blue_r, blue_c, i)

    print('-1')  # not found


if __name__ == '__main__':
    n, m = map(int, sys.stdin.readline().strip().split())
    board = [sys.stdin.readline().strip() for _ in range(n)]

    for i in range(n):
        for j in range(m):
            if board[i][j] == 'R':
                red_r, red_c = i, j
            if board[i][j] == 'B':
                blue_r, blue_c = i, j

    visited[red_r][red_c][blue_r][blue_c] = True
    queue.append((red_r, red_c, blue_r, blue_c, 0))
    solve()