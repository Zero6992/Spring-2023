#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

long long min_maximum_path(int n, int arr[]) {
    qsort(arr, n, sizeof(int), compare);

    long long dp[n][n];

    for (int i = 0; i < n; i++) {
        dp[i][i] = arr[i];
    }

    for (int l = 2; l <= n; l++) {
        for (int i = 0; i < n - l + 1; i++) {
            int j = i + l - 1;
            dp[i][j] = LLONG_MAX;
            for (int r = i; r <= j; r++) {
                long long left = (r > i) ? dp[i][r - 1] : 0;
                long long right = (r < j) ? dp[r + 1][j] : 0;
                long long current_max_path = arr[r] + (left > right ? left : right);
                dp[i][j] = (dp[i][j] < current_max_path) ? dp[i][j] : current_max_path;
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    long long result = min_maximum_path(n, arr);
    printf("%lld\n", result);

    return 0;
}
