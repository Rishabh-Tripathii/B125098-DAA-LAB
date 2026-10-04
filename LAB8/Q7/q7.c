#include <stdio.h>
#include <stdlib.h>

#define NEG_INF -1000000000

int main()
{
    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    // p[i] = price of a piece of length i
    int *p = (int *)malloc((n + 1) * sizeof(int));

    printf("Enter prices p[1] to p[%d]:\n", n);

    for (int i = 1; i <= n; i++)
    {
        printf("p[%d] = ", i);
        scanf("%d", &p[i]);
    }

    // dp[i] = maximum revenue for rod of length i
    int *dp = (int *)malloc((n + 1) * sizeof(int));

    // cut[i] = first piece length used in optimal solution for i
    int *cut = (int *)malloc((n + 1) * sizeof(int));

    dp[0] = 0;
    cut[0] = 0;

    /*
        Bottom-up dynamic programming
    */
    for (int i = 1; i <= n; i++)
    {
        dp[i] = NEG_INF;

        for (int j = 1; j <= i; j++)
        {
            int revenue = p[j] + dp[i - j];

            if (revenue > dp[i])
            {
                dp[i] = revenue;
                cut[i] = j;
            }
        }
    }

    printf("\nMaximum Revenue = %d\n", dp[n]);

    /*
        Reconstruct the optimal decomposition
    */
    printf("Optimal decomposition: ");

    int length = n;

    while (length > 0)
    {
        printf("%d", cut[length]);

        length -= cut[length];

        if (length > 0)
            printf(" + ");
    }

    printf("\n");

    /*
        Print DP table
    */
    printf("\nDP Table:\n");
    printf("Length\tRevenue\tFirst Cut\n");

    for (int i = 0; i <= n; i++)
    {
        printf("%d\t%d\t%d\n", i, dp[i], cut[i]);
    }

    free(p);
    free(dp);
    free(cut);

    return 0;
}