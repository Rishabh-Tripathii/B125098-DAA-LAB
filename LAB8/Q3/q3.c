#include <stdio.h>
#include <string.h>

void printLCS(char X[], char Y[], int m, int n)
{
    int dp[m + 1][n + 1];

    // Initialize first row and column
    for (int i = 0; i <= m; i++)
        dp[i][0] = 0;

    for (int j = 0; j <= n; j++)
        dp[0][j] = 0;

    // Build the DP table
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                if (dp[i - 1][j] > dp[i][j - 1])
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = dp[i][j - 1];
            }
        }
    }

    printf("Length of LCS = %d\n", dp[m][n]);

    // Reconstruct LCS
    int length = dp[m][n];
    char lcs[length + 1];

    lcs[length] = '\0';

    int i = m;
    int j = n;
    int index = length - 1;

    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index] = X[i - 1];

            i--;
            j--;
            index--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("LCS = %s\n", lcs);
}

int main()
{
    char X[100], Y[100];

    printf("Enter first sequence: ");
    scanf("%99s", X);

    printf("Enter second sequence: ");
    scanf("%99s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    printLCS(X, Y, m, n);

    return 0;
}