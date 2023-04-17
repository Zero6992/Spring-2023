#include <stdio.h>

int board[8192][8192];
int current_tile = 0;

void place_tan(int x, int y) {
    board[x][y] = current_tile;
}

void cover_board(int x, int y, int size, int black_x, int black_y) {
    if (size == 2) {
        current_tile++;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (x + i != black_x || y + j != black_y) {
                    place_tan(x + i, y + j);
                }
            }
        }
    } else {
        int half_size = size / 2;
        int new_black_x = black_x < x + half_size ? black_x : x + half_size - 1;
        int new_black_y = black_y < y + half_size ? black_y : y + half_size - 1;
        cover_board(x, y, half_size, new_black_x, new_black_y);

        new_black_x = black_x >= x + half_size ? black_x : x + half_size;
        new_black_y = black_y < y + half_size ? black_y : y +
        half_size - 1;
        cover_board(x + half_size, y, half_size, new_black_x, new_black_y);

        new_black_x = black_x < x + half_size ? black_x : x + half_size - 1;
        new_black_y = black_y >= y + half_size ? black_y : y + half_size;
        cover_board(x, y + half_size, half_size, new_black_x, new_black_y);

        new_black_x = black_x >= x + half_size ? black_x : x + half_size;
        new_black_y = black_y >= y + half_size ? black_y : y + half_size;
        cover_board(x + half_size, y + half_size, half_size, new_black_x, new_black_y);
    }
}

int main() {
    int N, L;
    scanf("%d %d", &N, &L);
    int black_grids[N][2];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &black_grids[i][0], &black_grids[i][1]);
        board[black_grids[i][0]][black_grids[i][1]] = 0;
    }

    cover_board(0, 0, L, black_grids[0][0], black_grids[0][1]);

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            printf("%d", board[i][j]);
            if (j < L - 1) {
                printf(" ");
            }
        }
    }

    return 0;
}
