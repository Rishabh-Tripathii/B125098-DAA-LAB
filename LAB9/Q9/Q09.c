#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

long long weights[MAX];
long long prefix[MAX + 1];
long long dp[MAX][MAX];
int split[MAX][MAX];

long long rangeSum(int i, int j) {
    return prefix[j + 1] - prefix[i];
}

void buildDP(int n) {
    int i, j, k, len;

    for (i = 0; i < n; i++) {
        dp[i][i] = 0;
        split[i][i] = -1;
    }

    for (len = 2; len <= n; len++) {
        for (i = 0; i + len <= n; i++) {
            j = i + len - 1;

            dp[i][j] = LLONG_MAX;
            split[i][j] = -1;

            long long sum = rangeSum(i, j);

            for (k = i; k < j; k++) {
                long long cost =
                    dp[i][k] + dp[k + 1][j] + sum;

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }
}

void printTree(int i, int j, int depth) {
    int d;

    for (d = 0; d < depth; d++)
        printf("  ");

    if (i == j) {
        printf("Leaf: w%d = %lld\n", i + 1, weights[i]);
        return;
    }

    printf("Internal node [%d, %d]\n", i + 1, j + 1);

    int k = split[i][j];

    printTree(i, k, depth + 1);
    printTree(k + 1, j, depth + 1);
}

void printLeafDepths(int i, int j, int depth) {
    if (i == j) {
        printf("w%d = %lld, depth = %d, contribution = %lld\n",
               i + 1, weights[i], depth,
               weights[i] * depth);
        return;
    }

    int k = split[i][j];

    printLeafDepths(i, k, depth + 1);
    printLeafDepths(k + 1, j, depth + 1);
}

int main(void) {
    int n, i;

    printf("Enter number of weights (1-%d): ", MAX);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Invalid number of weights.\n");
        return 1;
    }

    printf("Enter %d positive weights:\n", n);

    prefix[0] = 0;

    for (i = 0; i < n; i++) {
        if (scanf("%lld", &weights[i]) != 1 ||
            weights[i] <= 0) {
            printf("Invalid weight. Weights must be positive.\n");
            return 1;
        }

        prefix[i + 1] = prefix[i] + weights[i];
    }

    buildDP(n);

    printf("\nMinimum weighted path length = %lld\n",
           dp[0][n - 1]);

    printf("\nOptimal Alphabetic Binary Tree:\n");
    printTree(0, n - 1, 0);

    printf("\nLeaf depths and weighted contributions:\n");
    printLeafDepths(0, n - 1, 0);

    return 0;
}