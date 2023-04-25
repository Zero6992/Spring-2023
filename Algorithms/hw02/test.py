def min_maximum_path(n, arr):
    dp = [[0 for _ in range(n)] for _ in range(n)]

    for i in range(n):
        dp[i][i] = arr[i]

    for l in range(2, n+1):
        for i in range(n-l+1):
            j = i + l - 1
            dp[i][j] = float('inf')
            for r in range(i, j+1):
                left = dp[i][r-1] if r > i else 0
                right = dp[r+1][j] if r < j else 0
                current_max_path = arr[r] + max(left, right)
                dp[i][j] = min(dp[i][j], current_max_path)

    return dp[0][n-1]

# Read input
n = int(input())
arr = list(map(int, input().split()))

# Call the function and print the result
result = min_maximum_path(n, arr)
print(result)
