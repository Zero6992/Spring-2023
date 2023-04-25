#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MOD 1000000007

long long count_ways_to_pay(int n) {
    int coins[32], max_power;
    max_power = (int) log2(n);

    for (int i = 0; i <= max_power; i++) {
        coins[i] = 1 << i;
    }

    long long *dp = (long long *)calloc(n + 1, sizeof(long long));
    dp[0] = 1;

    for (int i = 0; i <= max_power; i++) {
        for (int j = coins[i]; j <= n; j++) {
            dp[j] = (dp[j] + dp[j - coins[i]]) % MOD;
        }
    }

    long long result = dp[n];
    free(dp);
    return result;
}

int main() {
    int n;

    scanf("%d", &n);

    long long ways_to_pay = count_ways_to_pay(n);
    printf("%lld", ways_to_pay);

    return 0;
}
