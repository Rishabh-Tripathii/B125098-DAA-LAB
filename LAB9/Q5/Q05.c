#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    printf("Enter the number of children: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of children.\n");
        return 1;
    }

    int *rating = (int *)malloc(n * sizeof(int));
    int *candies = (int *)malloc(n * sizeof(int));

    if (rating == NULL || candies == NULL) {
        printf("Memory allocation failed.\n");
        free(rating);
        free(candies);
        return 1;
    }

    printf("Enter the ratings of children:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &rating[i]);
    }

    // Initialize each child with one candy
    for (int i = 0; i < n; i++) {
        candies[i] = 1;
    }

    // Pass 1: Left to Right
    for (int i = 1; i < n; i++) {
        if (rating[i] > rating[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    // Pass 2: Right to Left
    for (int i = n - 2; i >= 0; i--) {
        if (rating[i] > rating[i + 1]) {
            if (candies[i] <= candies[i + 1]) {
                candies[i] = candies[i + 1] + 1;
            }
        }
    }

    // Calculate the minimum total candies
    long long total = 0;

    for (int i = 0; i < n; i++) {
        total += candies[i];
    }

    printf("\nRatings: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", rating[i]);
    }

    printf("\nCandies: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", candies[i]);
    }

    printf("\nMinimum total candies required: %lld\n", total);

    free(rating);
    free(candies);

    return 0;
}