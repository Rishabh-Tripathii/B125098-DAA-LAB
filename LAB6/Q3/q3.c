#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

void findLCS(char str1[], char str2[]) {
    int m = strlen(str1);
    int n = strlen(str2);
    // Create DP table
    int **dp = (int **)malloc((m + 1) * sizeof(int *));

    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    // Initialize first row and first column
    for (int i = 0; i <= m; i++) {
        dp[i][0] = 0;
    }

    for (int j = 0; j <= n; j++) {
        dp[0][j] = 0;
    }

    // Fill the DP table
    for (int i = 1; i <= m; i++) {

        for (int j = 1; j <= n; j++) {

            if (str1[i - 1] == str2[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else{
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // Length of LCS
    int lcsLength = dp[m][n];

    printf("Length of LCS = %d\n", lcsLength);

    // Allocate memory for LCS
    char *lcs = (char *)malloc((lcsLength + 1) * sizeof(char));
    int index = lcsLength;
    lcs[index] = '\0';
    // Backtracking to find LCS
    int i = m;
    int j = n;
    while (i > 0 && j > 0) {

        // Characters match
        if (str1[i - 1] == str2[j - 1]) {

            lcs[index - 1] = str1[i - 1];

            index--;
            i--;
            j--;
        }

        // Move up
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        }

        // Move left
        else {
            j--;
        }
    }

    printf("Longest Common Subsequence = %s\n", lcs);

    // Free memory
    free(lcs);

    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }

    free(dp);
}

int main() {

    char str1[100];
    char str2[100];

    printf("Enter first string: ");
    scanf("%99s", str1);

    printf("Enter second string: ");
    scanf("%99s", str2);

    findLCS(str1, str2);

    return 0;
}