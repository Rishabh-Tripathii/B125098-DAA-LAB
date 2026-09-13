#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

/* Check whether p occurs in an array */
int contains(Point arr[], int size, Point p) {
    for (int i = 0; i < size; i++) {
        if (arr[i].x == p.x && arr[i].y == p.y)
            return 1;
    }
    return 0;
}

int main() {
    int n;

    printf("Enter number of rows n: ");
    scanf("%d", &n);

    int total = n * (n + 1) / 2;

    Point *original = malloc(total * sizeof(Point));
    Point *target   = malloc(total * sizeof(Point));

    int no = 0, nt = 0;

    /* Original upward triangle:
       x >= 0, y >= 0, x + y <= n-1
    */
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n - x; y++) {
            original[no++] = (Point){x, y};
        }
    }

    /*
       Shift the inverted triangle by (-k, -k),
       where k = floor(n/3).
    */
    int k = n / 3;

    /*
       Target:
       -k <= x <= n-k-1
       -k <= y <= n-k-1
       x+y >= n-1-2k
    */
    for (int x = -k; x <= n - k - 1; x++) {
        for (int y = -k; y <= n - k - 1; y++) {

            if (x + y >= n - 1 - 2 * k) {
                target[nt++] = (Point){x, y};
            }
        }
    }

    /* Find coins that must move */
    Point *source = malloc(total * sizeof(Point));
    Point *dest   = malloc(total * sizeof(Point));

    int ns = 0, nd = 0;

    for (int i = 0; i < no; i++) {
        if (!contains(target, nt, original[i])) {
            source[ns++] = original[i];
        }
    }

    for (int i = 0; i < nt; i++) {
        if (!contains(original, no, target[i])) {
            dest[nd++] = target[i];
        }
    }

    printf("\nMinimum number of moves = %d\n", ns);

    printf("\nMoves:\n");

    for (int i = 0; i < ns; i++) {
        printf("(%d,%d) -> (%d,%d)\n",
               source[i].x, source[i].y,
               dest[i].x, dest[i].y);
    }

    printf("\nFormula gives: floor(n(n+1)/6) = %d\n",
           n * (n + 1) / 6);

    free(original);
    free(target);
    free(source);
    free(dest);

    return 0;
}