#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int distance;
    int fuel;
} Station;

// Sort stations by distance
int compare(const void *a, const void *b) {
    Station *s1 = (Station *)a;
    Station *s2 = (Station *)b;

    return (s1->distance > s2->distance) -
           (s1->distance < s2->distance);
}

// Insert fuel into max-heap
void insert(int heap[], int *size, int fuel) {
    int i = (*size)++;
    heap[i] = fuel;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent] >= heap[i])
            break;

        int temp = heap[parent];
        heap[parent] = heap[i];
        heap[i] = temp;

        i = parent;
    }
}

// Remove and return maximum fuel
int extractMax(int heap[], int *size) {
    int maximum = heap[0];

    heap[0] = heap[--(*size)];

    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < *size &&
            heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < *size &&
            heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest == i)
            break;

        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;

        i = largest;
    }

    return maximum;
}

// Find minimum refuelling stops
int minRefuelStops(
    int D,
    int F,
    Station stations[],
    int n
) {
    qsort(stations, n, sizeof(Station), compare);

    // Add target as the final destination
    Station *points = malloc((n + 1) * sizeof(Station));

    if (points == NULL)
        return -1;

    for (int i = 0; i < n; i++)
        points[i] = stations[i];

    points[n].distance = D;
    points[n].fuel = 0;

    // Max-heap of previously reachable stations
    int *heap = malloc((n > 0 ? n : 1) * sizeof(int));

    if (heap == NULL) {
        free(points);
        return -1;
    }

    int heapSize = 0;
    int currentFuel = F;
    int currentPosition = 0;
    int stops = 0;

    for (int i = 0; i <= n; i++) {
        int distance =
            points[i].distance - currentPosition;

        // Refuel until the next point is reachable
        while (currentFuel < distance) {
            if (heapSize == 0) {
                free(heap);
                free(points);
                return -1;
            }

            currentFuel += extractMax(heap, &heapSize);
            stops++;
        }

        currentFuel -= distance;
        currentPosition = points[i].distance;

        // Add fuel from the station just reached
        if (i < n) {
            insert(heap, &heapSize, points[i].fuel);
        }
    }

    free(heap);
    free(points);

    return stops;
}

int main() {
    int D, F, n;

    printf("Enter target distance: ");
    scanf("%d", &D);

    printf("Enter initial fuel: ");
    scanf("%d", &F);

    printf("Enter number of fuel stations: ");
    scanf("%d", &n);

    if (D < 0 || F < 0 || n < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    Station *stations =
        malloc((n > 0 ? n : 1) * sizeof(Station));

    if (stations == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter distance and fuel for each station:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %d",
              &stations[i].distance,
              &stations[i].fuel);

        if (stations[i].distance < 0 ||
            stations[i].distance > D ||
            stations[i].fuel < 0) {
            printf("Invalid station data.\n");
            free(stations);
            return 1;
        }
    }

    int result = minRefuelStops(D, F, stations, n);

    if (result == -1) {
        printf("Target cannot be reached.\n");
    } else {
        printf("Minimum refuelling stops: %d\n", result);
    }

    free(stations);

    return 0;
}