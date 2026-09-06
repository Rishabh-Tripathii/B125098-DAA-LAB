#include <stdio.h>
#include <stdlib.h>
int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int n, int weights[], int profits[], int W) {

    // Create DP table
    int **dp = (int **)malloc((n + 1) * sizeof(int *));

    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((W + 1) * sizeof(int));
    }
    // Initialize first row and first column
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
    for (int w = 0; w <= W; w++) {
        dp[0][w] = 0;
    }
    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            // If current item's weight is greater
            // than the current capacity
            if (weights[i - 1] > w) {
                dp[i][w] = dp[i - 1][w];
            }
            else {
                // Don't take the item
                int exclude = dp[i - 1][w];

                // Take the item
                int include = profits[i - 1]
                            + dp[i - 1][w - weights[i - 1]];

                dp[i][w] = max(include, exclude);
            }
        }
    }

    int answer = dp[n][W];
    // Free memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);
    return answer;
}

int main() {

    int n, W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int *weights = (int *)malloc(n * sizeof(int));
    int *profits = (int *)malloc(n * sizeof(int));

    printf("Enter weights of items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }

    printf("Enter profits of items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &profits[i]);
    }

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    int result = knapsack(n, weights, profits, W);

    printf("Maximum profit = %d\n", result);

    free(weights);
    free(profits);

    return 0;
}