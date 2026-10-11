#include <stdio.h>

#define MAX 1000

int heap[MAX];
int heapSize = 0;

// Swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Insert an element into the min-heap
void insert(int value) {
    if (heapSize >= MAX) {
        printf("Heap capacity exceeded.\n");
        return;
    }

    int i = heapSize;
    heap[heapSize++] = value;

    // Heapify upward
    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent] <= heap[i])
            break;

        swap(&heap[parent], &heap[i]);
        i = parent;
    }
}

// Remove and return the minimum element
int extractMin() {
    int minValue = heap[0];

    heap[0] = heap[--heapSize];

    int i = 0;

    // Heapify downward
    while (1) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < heapSize &&
            heap[left] < heap[smallest]) {
            smallest = left;
        }

        if (right < heapSize &&
            heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return minValue;
}

// Calculate minimum cost to connect all sticks
long long minimumCost(int n) {
    if (n <= 1)
        return 0;

    long long totalCost = 0;

    while (heapSize > 1) {
        int x = extractMin();
        int y = extractMin();

        long long cost = (long long)x + y;

        totalCost += cost;

        insert((int)cost);
    }

    return totalCost;
}

int main() {
    int n;

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    if (n < 0 || n > MAX) {
        printf("Invalid number of sticks.\n");
        return 1;
    }

    printf("Enter stick lengths:\n");

    for (int i = 0; i < n; i++) {
        int length;
        scanf("%d", &length);

        if (length < 0) {
            printf("Stick lengths cannot be negative.\n");
            return 1;
        }

        insert(length);
    }

    long long result = minimumCost(n);

    printf("Minimum total cost: %lld\n", result);

    return 0;
}