#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long comparisons = 0;

/* Comparison function for qsort() */
int compare(const void *a, const void *b) {
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

/* Binary Search */
int binarySearch(int arr[], int n, int target) {

    int low = 0;
    int high = n - 1;

    while (low <= high) {

        int mid = low + (high - low) / 2;

        comparisons++;

        if (arr[mid] == target) {
            return 1;
        }

        comparisons++;

        if (arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return 0;
}

int main() {

    int n, x;

    printf("Enter size of both sets: ");
    scanf("%d", &n);

    int *S1 = malloc(n * sizeof(int));
    int *S2 = malloc(n * sizeof(int));

    printf("Enter elements of S1:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &S1[i]);
    }

    printf("Enter elements of S2:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &S2[i]);
    }

    printf("Enter x: ");
    scanf("%d", &x);

    /* Reset comparison counter */
    comparisons = 0;

    clock_t start = clock();

    /*
       Step 1:
       Sort S2.
       Complexity = O(n log n)
    */
    qsort(S2, n, sizeof(int), compare);

    int found = 0;
    int first = 0;
    int second = 0;

    /*
       Step 2:
       For every element of S1, search for x - S1[i]
       in S2 using binary search.
    */
    for (int i = 0; i < n; i++) {

        int required = x - S1[i];

        if (binarySearch(S2, n, required)) {

            found = 1;
            first = S1[i];
            second = required;

            break;
        }
    }

    clock_t end = clock();

    double time_taken =
        (double)(end - start) / CLOCKS_PER_SEC;

    if (found) {
        printf("\nPair found!\n");
        printf("%d + %d = %d\n", first, second, x);
    }
    else {
        printf("\nNo such pair exists.\n");
    }

    printf("\nNumber of comparisons = %lld\n",
           comparisons);

    printf("Execution time = %f seconds\n",
           time_taken);

    printf("\nTime Complexity: O(n log n)\n");
    printf("Space Complexity: O(n)\n");

    free(S1);
    free(S2);

    return 0;
}