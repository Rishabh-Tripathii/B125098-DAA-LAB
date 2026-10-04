#include <stdio.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int LIS(int A[], int n)
{
    int dp[n];

    // Every element is an LIS of length 1
    for (int i = 0; i < n; i++)
        dp[i] = 1;

    // Calculate LIS ending at each position
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (A[j] < A[i])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    // Find maximum value in dp[]
    int result = 0;

    for (int i = 0; i < n; i++)
    {
        result = max(result, dp[i]);
    }

    return result;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int A[n];

    printf("Enter array elements: ");

    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    int result = LIS(A, n);

    printf("Length of Longest Increasing Subsequence = %d\n",
           result);

    return 0;
}