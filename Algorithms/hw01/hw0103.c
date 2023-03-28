#include <stdio.h>

int board[8192][8192];
int tile = 1;

void fill_board(int x, int y, int size, int bx, int by) {
    if (size == 2) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (x + i != bx || y + j != by) {
                    board[x + i][y + j] = tile;
                }
            }
        }
        tile++;
        return;
    }

    int half = size / 2;

    if (bx < x + half && by < y + half) {
        fill_board(x, y, half, bx, by);
    } else {
        board[x + half - 1][y + half - 1] = tile;
        fill_board(x, y, half, x + half - 1, y + half - 1);
    }

    if (bx < x + half && by >= y + half) {
        fill_board(x, y + half, half, bx, by);
    } else {
        board[x + half - 1][y + half] = tile;
        fill_board(x, y + half, half, x + half - 1, y + half);
    }

    if (bx >= x + half && by < y + half) {
        fill_board(x + half, y, half, bx, by);
    } else {
        board[x + half][y + half - 1] = tile;
        fill_board(x + half, y, half, x + half, y + half - 1);
    }

    if (bx >= x + half && by >= y + half) {
        fill_board(x + half, y + half, half, bx, by);
    } else {
        board[x + half][y + half] = tile;
        fill_board(x + half, y + half, half, x + half, y + half);
    }

    tile++;
}

int main() {
    int n, l;
    scanf("%d%d", &n, &l);

    int x, y;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &x, &y);
        board[x][y] = -1;
    }

    fill_board(0, 0, l, x, y);

    for (int i = 0; i < l; i++) {
        for (int j = 0; j < l; j++) {
            printf("%d ", board[i][j] == -1 ? 0 : board[i][j]);
        }
        printf("\n");
    }

    return 0;
}
