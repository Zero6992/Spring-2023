#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, M, i, u, v, k;
    scanf("%d %d", &N, &M);

    int* T = (int*)malloc(N * sizeof(int));
    int* progress = (int*)calloc(N + 1, sizeof(int));

    for (i = 0; i < N; ++i) {
        scanf("%d", &T[i]);
    }

    int day;
    for (day = 1; day <= M; ++day) {
        scanf("%d %d %d", &u, &v, &k);
        progress[u] += k;
        progress[v + 1] -= k;

        int sum = 0, goal_achieved = 1;
        for (i = 0; i < N; ++i) {
            sum += progress[i];
            if (sum < T[i]) {
                goal_achieved = 0;
                break;
            }
        }

        if (goal_achieved) {
            printf("%d\n", day);
            break;
        }
    }

    if (day > M) {
        printf("-1\n");
    }

    free(T);
    free(progress);

    return 0;
}