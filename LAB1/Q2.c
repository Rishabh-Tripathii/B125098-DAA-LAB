#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void simulateCoin(double probability, int trials)
{
    int heads = 0;

    for (int i = 0; i < trials; i++)
    {
        double r = (double)rand() / RAND_MAX;

        if (r < probability)
            heads++;
    }

    double observed = (double)heads / trials;

    printf("\nCoin with P(Head) = %.1f\n", probability);
    printf("-------------------------\n");
    printf("Total Tosses : %d\n", trials);
    printf("Heads        : %d\n", heads);
    printf("Tails        : %d\n", trials - heads);
    printf("Observed P(H): %.5f\n", observed);
}

int main()
{
    int trials;

    printf("Enter number of tosses: ");
    scanf("%d", &trials);

    srand(time(NULL));

    double probabilities[] = {0.5, 0.3, 0.7, 0.9};

    int size = sizeof(probabilities) / sizeof(probabilities[0]);

    printf("\n===== Coin Toss Simulation =====\n");

    for (int i = 0; i < size; i++)
        simulateCoin(probabilities[i], trials);

    return 0;
}