#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int heap[MAX];
int size = 0;

// Swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Insert an element into the Max-Heap
void insert(int value) {
    int i = size;
    heap[size++] = value;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent] >= heap[i])
            break;

        swap(&heap[parent], &heap[i]);
        i = parent;
    }
}

// Remove and return the maximum element
int extractMax() {
    int maxValue = heap[0];

    heap[0] = heap[--size];

    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < size &&
            heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < size &&
            heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }

    return maxValue;
}

// Find the minimum element in the heap
int findMin() {
    int minValue = heap[0];

    for (int i = 1; i < size; i++) {
        if (heap[i] < minValue)
            minValue = heap[i];
    }

    return minValue;
}

// Minimise deviation
int minimumDeviation(int arr[], int n) {
    size = 0;

    int minDeviation;

    // Make every odd element even
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 != 0)
            arr[i] *= 2;

        insert(arr[i]);
    }

    // Initial deviation
    int minElement = findMin();
    int maxElement = heap[0];

    minDeviation = maxElement - minElement;

    // Greedily reduce the maximum element
    while (heap[0] % 2 == 0) {
        int maxValue = extractMax();

        maxValue /= 2;

        insert(maxValue);

        minElement = findMin();
        maxElement = heap[0];

        int deviation = maxElement - minElement;

        if (deviation < minDeviation)
            minDeviation = deviation;
    }

    return minDeviation;
}

int main() {
    int n;
    int arr[MAX];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter array elements:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);

        if (arr[i] <= 0) {
            printf("Elements must be positive.\n");
            return 1;
        }
    }

    int result = minimumDeviation(arr, n);

    printf("Minimum Deviation = %d\n", result);

    return 0;
}