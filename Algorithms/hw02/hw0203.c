#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int *route_a = (int *)a;
    int *route_b = (int *)b;

    if (route_a[0] == route_b[0]) {
        return route_b[1] - route_a[1];
    }

    return route_a[0] - route_b[0];
}

int binary_search(int *tails, int len, int target) {
    int left = 0, right = len - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (tails[mid] < target) {
            left = mid + 1;
        } else if (tails[mid] > target) {
            right = mid - 1;
        } else {
            return mid;
        }
    }

    return left;
}

int main() {
    int N, M, R;
    scanf("%d %d", &N, &M);
    scanf("%d", &R);

    int routes[R][2];
    for (int i = 0; i < R; i++) {
        scanf("%d %d", &routes[i][0], &routes[i][1]);
    }

    qsort(routes, R, sizeof(routes[0]), compare);

    int *tails = (int *)malloc(R * sizeof(int));
    int len = 0;

    for (int i = 0; i < R; i++) {
        int idx = binary_search(tails, len, routes[i][1]);
        if (idx == len) {
            tails[len++] = routes[i][1];
        } else {
            tails[idx] = routes[i][1];
        }
    }

    printf("%d\n", len);

    free(tails);
    return 0;
}
