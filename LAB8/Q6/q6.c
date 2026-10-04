#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

#define MATCH 0
#define INSERT 1
#define DELETE 2
#define SUBSTITUTE 3

int dp[MAX + 1][MAX + 1];
int parent[MAX + 1][MAX + 1];

void traceback(char A[], char B[], int m, int n)
{
    int operations[MAX * 2];
    int count = 0;

    int i = m;
    int j = n;

    while (i > 0 || j > 0)
    {
        operations[count++] = parent[i][j];

        if (parent[i][j] == MATCH ||
            parent[i][j] == SUBSTITUTE)
        {
            i--;
            j--;
        }
        else if (parent[i][j] == INSERT)
        {
            j--;
        }
        else
        {
            i--;
        }
    }

    printf("\nTraceback Operations:\n");

    for (int k = count - 1; k >= 0; k--)
    {
        if (operations[k] == MATCH)
            printf("MATCH\n");

        else if (operations[k] == INSERT)
            printf("INSERT '%c'\n", B[n--]);

        else if (operations[k] == DELETE)
            printf("DELETE '%c'\n", A[m--]);

        else
            printf("SUBSTITUTE '%c' -> '%c'\n", A[m--], B[n--]);
    }
}

int main()
{
    char A[MAX], B[MAX];

    printf("Enter string A: ");
    scanf("%s", A);

    printf("Enter string B: ");
    scanf("%s", B);

    int m = strlen(A);
    int n = strlen(B);

    dp[0][0] = 0;

    for (int i = 1; i <= m; i++)
    {
        dp[i][0] = i;
        parent[i][0] = DELETE;
    }

    for (int j = 1; j <= n; j++)
    {
        dp[0][j] = j;
        parent[0][j] = INSERT;
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
                parent[i][j] = MATCH;
            }
            else
            {
                int insert = dp[i][j - 1] + 1;
                int delete = dp[i - 1][j] + 1;
                int substitute = dp[i - 1][j - 1] + 1;

                dp[i][j] = insert;
                parent[i][j] = INSERT;

                if (delete < dp[i][j])
                {
                    dp[i][j] = delete;
                    parent[i][j] = DELETE;
                }

                if (substitute < dp[i][j])
                {
                    dp[i][j] = substitute;
                    parent[i][j] = SUBSTITUTE;
                }
            }
        }
    }

    printf("\nMinimum Edit Distance = %d\n", dp[m][n]);

    traceback(A, B, m, n);

    return 0;
}