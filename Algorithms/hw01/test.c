#include <stdio.h>
#include <math.h>

int tile = 1;

void fill_board(int x, int y, int l, int board[][8192], int black_x, int black_y) {
    if (l == 1) {
        return;
    }
    
    int sub_l = l / 2;
    int center_x = x + sub_l;
    int center_y = y + sub_l;
    
    if (black_x < center_x && black_y < center_y) {
        fill_board(x, y, sub_l, board, black_x, black_y);
    } else {
        board[center_y - 1][center_x - 1] = tile;
        fill_board(x, y, sub_l, board, center_x - 1, center_y - 1);
    }
    
    if (black_x >= center_x && black_y < center_y) {
        fill_board(center_x, y, sub_l, board, black_x, black_y);
    } else {
        board[center_y - 1][center_x] = tile;
        fill_board(center_x, y, sub_l, board, center_x, center_y - 1);
    }
    
    if (black_x < center_x && black_y >= center_y) {
        fill_board(x, center_y, sub_l, board, black_x, black_y);
    } else {
        board[center_y][center_x - 1] = tile;
        fill_board(x, center_y, sub_l, board, center_x - 1, center_y);
    }
    
    if (black_x >= center_x && black_y >= center_y) {
        fill_board(center_x, center_y, sub_l, board, black_x, black_y);
    } else {
        board[center_y][center_x] = tile;
        fill_board(center_x, center_y, sub_l, board, center_x, center_y);
    }
    
    tile++;
}

int main() {
    int n, l;
    scanf("%d %d", &n, &l);
    
    int board[8192][8192] = {0};
    
    int black_x, black_y;
    scanf("%d %d", &black_x, &black_y);
    board[black_y][black_x] = 0;
    
    fill_board(0, 0, l, board, black_x, black_y);
    
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < l; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

