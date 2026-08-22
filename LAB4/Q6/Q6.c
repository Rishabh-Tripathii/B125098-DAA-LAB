#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int position;
    int type;       // 1 = start, -1 = end
} Event;

long long comparisons = 0;

/*
 * Compare two events.
 *
 * Smaller position comes first.
 * If positions are equal, START comes before END
 * because endpoints count as being inside the interval.
 */
int compareEvents(Event a, Event b)
{
    comparisons++;

    if (a.position < b.position)
        return 1;

    if (a.position > b.position)
        return 0;

    /* Same position: start before end */
    return a.type > b.type;
}

/* Merge two sorted portions */
void merge(Event arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Event *L = malloc(n1 * sizeof(Event));
    Event *R = malloc(n2 * sizeof(Event));

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {

        if (compareEvents(L[i], R[j]))
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
void mergeSort(Event arr[], int left, int right)
{
    if (left < right) {

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Event *events = malloc(2 * n * sizeof(Event));

    printf("Enter intervals (left right):\n");

    for (int i = 0; i < n; i++) {

        int l, r;

        scanf("%d %d", &l, &r);

        events[2 * i].position = l;
        events[2 * i].type = 1;

        events[2 * i + 1].position = r;
        events[2 * i + 1].type = -1;
    }

    comparisons = 0;

    clock_t start = clock();

    /* Sort all 2n events */
    mergeSort(events, 0, 2 * n - 1);

    int current = 0;
    int maxCount = 0;
    int bestPoint = 0;

    /* Sweep through the events */
    for (int i = 0; i < 2 * n; i++) {

        if (events[i].type == 1) {

            current++;

            if (current > maxCount) {
                maxCount = current;
                bestPoint = events[i].position;
            }
        }
        else {
            current--;
        }
    }

    clock_t end = clock();

    double timeTaken =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nPoint with maximum overlap = %d\n",
           bestPoint);

    printf("Maximum number of intervals = %d\n",
           maxCount);

    printf("Number of comparisons = %lld\n",
           comparisons);

    printf("Execution time = %f seconds\n",
           timeTaken);

    printf("\nTime Complexity: O(n log n)\n");
    printf("Space Complexity: O(n)\n");

    free(events);

    return 0;
}