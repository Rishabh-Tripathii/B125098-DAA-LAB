#include <stdio.h>

long long countWays(int coins[], int n, int V)
{
    long long dp[V + 1];

    // Initially, there are 0 ways to make each amount
    for (int i = 0; i <= V; i++)
        dp[i] = 0;

    // One way to make amount 0: choose nothing
    dp[0] = 1;

    // Process each coin
    for (int i = 0; i < n; i++)
    {
        // Consider all amounts that can use this coin
        for (int amount = coins[i]; amount <= V; amount++)
        {
            dp[amount] += dp[amount - coins[i]];
        }
    }

    return dp[V];
}

int main()
{
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter coin denominations: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter target amount: ");
    scanf("%d", &V);

    long long result = countWays(coins, n, V);

    printf("Total number of combinations = %lld\n", result);

    return 0;
}