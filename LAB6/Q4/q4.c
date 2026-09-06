#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int min(int a, int b) {
    return (a < b) ? a : b;
}
int matrixChainMultiplication(int arr[], int N) {

    // dp[i][j] = minimum cost of multiplying
    // matrices Ai to Aj
    int **dp = (int **)malloc(N * sizeof(int *));

    for (int i = 0; i < N; i++) {
        dp[i] = (int *)malloc(N * sizeof(int));
    }

    // Base case:
    // Multiplying one matrix requires 0 operations
    for (int i = 1; i < N; i++) {
        dp[i][i] = 0;
    }

    // chainLength is the number of matrices in the chain
    for (int chainLength = 2; chainLength <= N - 1; chainLength++) {

        for (int i = 1; i <= N - chainLength; i++) {

            int j = i + chainLength - 1;

            dp[i][j] = INT_MAX;

            // Try every possible split
            for (int k = i; k < j; k++) {

                int cost = dp[i][k]
                         + dp[k + 1][j]
                         + arr[i - 1] * arr[k] * arr[j];

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    int answer = dp[1][N - 1];

    // Free memory
    for (int i = 0; i < N; i++) {
        free(dp[i]);
    }

    free(dp);

    return answer;
}

int main() {

    int N;

    printf("Enter N: ");
    scanf("%d", &N);

    int *arr = (int *)malloc(N * sizeof(int));

    printf("Enter the dimensions of the matrices:\n");

    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    int result = matrixChainMultiplication(arr, N);

    printf("Minimum number of scalar multiplications = %d\n", result);

    free(arr);

    return 0;
}

//Time complexity is O(n^3)