#include <stdio.h>

int comparisons = 0;

struct Result {
    int min;
    int max;
};

struct Result maxMin(int a[], int low, int high)
{
    struct Result result;
    struct Result left, right;

    // Only one element
    if (low == high)
    {
        result.min = result.max = a[low];
        return result;
    }

    // Two elements
    if (high == low + 1)
    {
        comparisons++;

        if (a[low] < a[high])
        {
            result.min = a[low];
            result.max = a[high];
        }
        else
        {
            result.min = a[high];
            result.max = a[low];
        }

        return result;
    }

    // Divide
    int mid = (low + high) / 2;

    // Conquer
    left = maxMin(a, low, mid);
    right = maxMin(a, mid + 1, high);

    // Combine: compare maximums
    comparisons++;
    if (left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;

    // Combine: compare minimums
    comparisons++;
    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;

    return result;
}

int main()
{
    int n;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    struct Result result = maxMin(a, 0, n - 1);

    printf("\nMinimum element = %d\n", result.min);
    printf("Maximum element = %d\n", result.max);
    printf("Number of comparisons = %d\n", comparisons);

    printf("3n/2 = %.1f\n", 1.5 * n);

    return 0;
}