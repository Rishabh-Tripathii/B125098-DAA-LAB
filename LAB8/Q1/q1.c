#include <stdio.h>
#include <limits.h>
int min(int a, int b) {
    return (a < b) ? a : b;
}
int minCoins(int coins[], int n, int V) {
    int dp[V + 1];

    // Base case
    dp[0] = 0;

    // Initialize other values to infinity
    for (int i = 1; i <= V; i++)
        dp[i] = INT_MAX;

    // Calculate minimum coins for every amount
    for (int amount = 1; amount <= V; amount++) {
        for (int i = 0; i < n; i++) {

            if (coins[i] <= amount && dp[amount - coins[i]] != INT_MAX) {
                dp[amount] = min(dp[amount],
                                 dp[amount - coins[i]] + 1);
            }
        }
    }

    // If target cannot be formed
    if (dp[V] == INT_MAX)
        return -1;

    return dp[V];
}

int main() {
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter coin denominations: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter target amount: ");
    scanf("%d", &V);

    int result = minCoins(coins, n, V);

    if (result == -1)
        printf("Target amount cannot be formed.\n");
    else
        printf("Minimum number of coins = %d\n", result);

    return 0;
}