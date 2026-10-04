#include <stdio.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int maxSumIncreasingSubsequence(int A[], int n)
{
    int dp[n];

    // Each element by itself forms
    // an increasing subsequence
    for (int i = 0; i < n; i++)
        dp[i] = A[i];

    // Calculate maximum sum ending at each index
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (A[j] < A[i])
            {
                dp[i] = max(dp[i], dp[j] + A[i]);
            }
        }
    }

    // Find maximum sum
    int result = dp[0];

    for (int i = 1; i < n; i++)
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

    int result = maxSumIncreasingSubsequence(A, n);

    printf("Maximum Sum of Increasing Subsequence = %d\n",
           result);

    return 0;
}