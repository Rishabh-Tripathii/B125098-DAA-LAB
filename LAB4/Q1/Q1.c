#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define BLUE 1
#define YELLOW 2

typedef struct {
    int number;
    int colour;
} Item;

long long comparisons = 0;

void sortByColour(Item arr[], int n) {

    Item *red = malloc(n * sizeof(Item));
    Item *blue = malloc(n * sizeof(Item));
    Item *yellow = malloc(n * sizeof(Item));

    int r = 0, b = 0, y = 0;

    /*
       Distribute elements into three arrays.

       We count every colour comparison:
       arr[i].colour == RED
       arr[i].colour == BLUE
    */
    for (int i = 0; i < n; i++) {

        comparisons++;
        if (arr[i].colour == RED) {
            red[r++] = arr[i];
        }
        else {
            comparisons++;
            if (arr[i].colour == BLUE) {
                blue[b++] = arr[i];
            }
            else {
                yellow[y++] = arr[i];
            }
        }
    }

    /*
       Combine the three arrays:
       RED -> BLUE -> YELLOW
    */
    int k = 0;

    for (int i = 0; i < r; i++)
        arr[k++] = red[i];

    for (int i = 0; i < b; i++)
        arr[k++] = blue[i];

    for (int i = 0; i < y; i++)
        arr[k++] = yellow[i];

    free(red);
    free(blue);
    free(yellow);
}
void printColour(int colour) {
    if (colour == RED)
        printf("Red");
    else if (colour == BLUE)
        printf("Blue");
    else
        printf("Yellow");
}

int main() {

    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item *arr = malloc(n * sizeof(Item));

    printf("Enter number and colour (R/B/Y):\n");

    /*
       Input is assumed to already be sorted by number.
    */
    for (int i = 0; i < n; i++) {

        char c;

        scanf("%d %c", &arr[i].number, &c);

        if (c == 'R' || c == 'r')
            arr[i].colour = RED;

        else if (c == 'B' || c == 'b')
            arr[i].colour = BLUE;

        else
            arr[i].colour = YELLOW;
    }

    /*
       Measure execution time of the sorting algorithm.
    */
    clock_t start = clock();

    sortByColour(arr, n);

    clock_t end = clock();

    double time_taken =
        (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nSorted array:\n");

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i].number);
        printColour(arr[i].colour);
        printf("\n");
    }

    printf("\nNumber of colour comparisons = %lld\n",
           comparisons);

    printf("Execution time = %f seconds\n",
           time_taken);

    printf("\nTime Complexity: O(n)\n");
    printf("Space Complexity: O(n)\n");
    free(arr);
    return 0;
}
//Through the number of comparisions we can see that we are taking O(2n) in the worst case i.e O(n) time complexity