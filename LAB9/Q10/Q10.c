#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_LEN 10000

char strings[MAX_N][MAX_LEN];

/* Find the maximum suffix-prefix overlap */
int findOverlap(const char *a, const char *b) {
    int lenA = strlen(a);
    int lenB = strlen(b);

    int maxOverlap = lenA < lenB ? lenA : lenB;

    for (int len = maxOverlap; len > 0; len--) {
        if (strncmp(a + lenA - len, b, len) == 0) {
            return len;
        }
    }

    return 0;
}

/* Merge two strings using their maximum overlap */
void mergeStrings(char *a, const char *b, int overlap) {
    strcat(a, b + overlap);
}

/* Greedy shortest common superstring */
void greedySuperstring(int n) {
    while (n > 1) {
        int maxOverlap = -1;
        int bestI = -1;
        int bestJ = -1;

        /* Find the pair with maximum overlap */
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    continue;
                }

                int overlap =
                    findOverlap(strings[i], strings[j]);

                if (overlap > maxOverlap) {
                    maxOverlap = overlap;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        /* No positive overlap remains */
        if (maxOverlap <= 0) {
            break;
        }

        /* Merge the selected pair */
        mergeStrings(
            strings[bestI],
            strings[bestJ],
            maxOverlap
        );

        /* Remove the second string */
        for (int i = bestJ; i < n - 1; i++) {
            strcpy(strings[i], strings[i + 1]);
        }

        n--;
    }

    /* Concatenate remaining strings if necessary */
    if (n > 1) {
        for (int i = 1; i < n; i++) {
            strcat(strings[0], strings[i]);
        }
    }

    printf("\nGreedy Superstring: %s\n", strings[0]);
    printf("Length: %zu\n", strlen(strings[0]));
}

int main() {
    int n;

    printf("Enter number of strings: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_N) {
        printf("Invalid number of strings.\n");
        return 1;
    }

    printf("Enter the strings:\n");

    for (int i = 0; i < n; i++) {
        scanf("%9999s", strings[i]);
    }

    greedySuperstring(n);

    return 0;
}