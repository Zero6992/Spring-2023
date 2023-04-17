#include <stdio.h>
#include <stdlib.h>

int id = 1;

void cover_board(int x, int y, int size, int tx, int ty, int **board)
{
    if (size == 2)
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                if (x + i != tx || y + j != ty)
                {
                    board[x + i][y + j] = id;
                }
            }
        }
        id++;
        return;
    }

    int t = size / 2;
    int offsetX[4] = {0, t, 0, t};
    int offsetY[4] = {0, 0, t, t};

    for (int i = 0; i < 4; i++)
    {
        int newX = x + offsetX[i];
        int newY = y + offsetY[i];

        if (tx >= newX && tx < newX + t && ty >= newY && ty < newY + t)
        {
            cover_board(newX, newY, t, tx, ty, board);
        }
        else
        {
            int cx = newX + t - 1;
            int cy = newY + t - 1;
            board[cx][cy] = id;
            cover_board(newX, newY, t, cx, cy, board);
        }
    }
    id++;
}

int main()
{
    int N, L;
    scanf("%d%d", &N, &L);

    int **board = (int **)malloc(sizeof(int *) * L);
    for (int i = 0; i < L; i++)
    {
        board[i] = (int *)malloc(sizeof(int) * L);
        for (int j = 0; j < L; j++)
        {
            board[i][j] = 0;
        }
    }
    for (int i = 0; i < N; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        board[x][y] = 0;
    }

    cover_board(0, 0, L, 0, 0, board);

    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < L; j++)
        {
            printf("%d", board[i][j]);
            if (j < L - 1)
            {
                printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < L; i++)
    {
        free(board[i]);
    }
    free(board);

    return 0;
}