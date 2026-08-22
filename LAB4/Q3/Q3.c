#include <stdio.h>
#include <stdlib.h>
#include <time.h>
long long comparisons = 0;
int found = 0;
/* Comparison function for qsort */
int compare(const void *a, const void *b)
{
    comparisons++;

    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    else
        return 0;
}

/* Check whether an index is already selected */
int isSelected(int index, int selected[], int count)
{
    for (int i = 0; i < count; i++) {
        comparisons++;

        if (selected[i] == index)
            return 1;
    }

    return 0;
}

/* Binary search for target */
int binarySearch(int S[], int n, int target,
                 int selected[], int count)
{
    int low = 0;
    int high = n - 1;

    while (low <= high) {

        int mid = low + (high - low) / 2;

        comparisons++;

        if (S[mid] == target) {

            /*
             * Make sure we are not using an already
             * selected element.
             */
            if (!isSelected(mid, selected, count))
                return mid;

            /*
             * Since S is a set, there cannot be another
             * occurrence of the same value.
             */
            return -1;
        }

        comparisons++;

        if (S[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

/*
 * Recursively choose k-1 elements.
 */
void findCombination(int S[], int n, int k,
                     int depth, int start,
                     int selected[], int T,
                     int currentSum)
{
    if (found)
        return;

    /*
     * We have selected k-1 elements.
     * Search for the kth element.
     */
    if (depth == k - 1) {

        int required = T - currentSum;

        int index = binarySearch(
            S, n, required, selected, depth
        );

        if (index != -1) {

            found = 1;

            printf("\nPair/combination found:\n");

            for (int i = 0; i < depth; i++)
                printf("%d ", S[selected[i]]);

            printf("%d", S[index]);
            printf("\nSum = %d\n", T);
        }

        return;
    }

    /*
     * Choose the next element.
     * Indices are increasing, so the same element
     * cannot be selected twice.
     */
    for (int i = start; i < n; i++) {

        selected[depth] = i;

        findCombination(
            S,
            n,
            k,
            depth + 1,
            i + 1,
            selected,
            T,
            currentSum + S[i]
        );

        if (found)
            return;
    }
}

int main()
{
    int n, k, T;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter k: ");
    scanf("%d", &k);

    printf("Enter target T: ");
    scanf("%d", &T);

    if (k > n || k < 2) {
        printf("Invalid value of k.\n");
        return 0;
    }

    int *S = malloc(n * sizeof(int));
    int *selected = malloc((k - 1) * sizeof(int));

    printf("Enter %d elements of the set:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &S[i]);

    comparisons = 0;
    found = 0;

    clock_t start = clock();

    /* Sort the set */
    qsort(S, n, sizeof(int), compare);

    /* Find k elements whose sum is T */
    findCombination(
        S, n, k,
        0, 0,
        selected,
        T, 0
    );
    clock_t end = clock();
    double time_taken =
        (double)(end - start) / CLOCKS_PER_SEC;
    if (!found)
        printf("\nNo combination of %d elements found.\n", k);
    printf("\nNumber of comparisons = %lld\n",
           comparisons);
    printf("Execution time = %f seconds\n",
           time_taken);
    printf("\nTheoretical Time Complexity: O(n^(k-1) log n)\n");
    printf("Space Complexity: O(k)\n");
    free(S);
    free(selected);
    return 0;
}