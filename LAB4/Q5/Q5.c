#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int start;
    int end;
} Interval;

long long comparisons = 0;

/* Compare intervals by starting point */
int compareIntervals(Interval a, Interval b)
{
    comparisons++;

    return a.start < b.start;
}

/* Merge two sorted portions */
void merge(Interval arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Interval *L = malloc(n1 * sizeof(Interval));
    Interval *R = malloc(n2 * sizeof(Interval));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {

        if (compareIntervals(L[i], R[j]))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

/* Merge Sort */
void mergeSort(Interval arr[], int left, int right)
{
    if (left < right) {

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

/* Merge overlapping intervals */
int mergeIntervals(Interval arr[], int n, Interval result[])
{
    if (n == 0)
        return 0;

    int count = 0;

    int currentStart = arr[0].start;
    int currentEnd = arr[0].end;

    for (int i = 1; i < n; i++) {

        /*
         * If the next interval overlaps with
         * the current interval.
         */
        comparisons++;

        if (arr[i].start <= currentEnd) {

            if (arr[i].end > currentEnd)
                currentEnd = arr[i].end;
        }
        else {

            result[count].start = currentStart;
            result[count].end = currentEnd;
            count++;

            currentStart = arr[i].start;
            currentEnd = arr[i].end;
        }
    }

    /* Add the last interval */
    result[count].start = currentStart;
    result[count].end = currentEnd;
    count++;

    return count;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Interval *arr = malloc(n * sizeof(Interval));
    Interval *result = malloc(n * sizeof(Interval));

    printf("Enter intervals (start end):\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].start, &arr[i].end);
    }

    comparisons = 0;

    clock_t start = clock();

    /* Sort intervals by starting point */
    mergeSort(arr, 0, n - 1);

    /* Merge overlapping intervals */
    int resultCount = mergeIntervals(arr, n, result);

    clock_t end = clock();

    double timeTaken =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nMerged intervals:\n");

    for (int i = 0; i < resultCount; i++) {
        printf("(%d, %d)\n",
               result[i].start,
               result[i].end);
    }

    printf("\nNumber of comparisons = %lld\n",
           comparisons);

    printf("Execution time = %f seconds\n",
           timeTaken);

    printf("\nTime Complexity: O(n log n)\n");
    printf("Space Complexity: O(n)\n");

    free(arr);
    free(result);

    return 0;
}