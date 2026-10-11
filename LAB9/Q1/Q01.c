#include <stdio.h>

typedef struct {
int id;
double value;
double weight;
double decay;
double fraction;
} Item;

int main() {
int n;
double W, time = 0.0, totalValue = 0.0;

printf("Enter number of items: ");
scanf("%d", &n);

Item items[n];

printf("Enter knapsack capacity: ");
scanf("%lf", &W);

for (int i = 0; i < n; i++) {
    items[i].id = i + 1;

    printf("Enter value, weight and decay rate of item %d: ", i + 1);
    scanf("%lf %lf %lf",&items[i].value,&items[i].weight,&items[i].decay);

    items[i].fraction = 0.0;
}

// Greedily select the item with the highest
// positive effective value density.
while (W > 0.0) {
    int best = -1;
    double bestDensity = 0.0;

    for (int i = 0; i < n; i++) {
        if (items[i].fraction >= 1.0)
            continue;

        double density =
            items[i].value / items[i].weight
            - items[i].decay * time;

        if (density > bestDensity) {
            bestDensity = density;
            best = i;
        }
    }

    // Stop if no item has positive effective density.
    if (best == -1)
        break;

    double remainingFraction = 1.0 - items[best].fraction;
    double availableWeight =
        remainingFraction * items[best].weight;

    double takenWeight;

    if (availableWeight <= W)
        takenWeight = availableWeight;
    else
        takenWeight = W;

    double takenFraction =
        takenWeight / items[best].weight;

    items[best].fraction += takenFraction;

    // Value is calculated using the density at selection time.
    totalValue += takenWeight * bestDensity;

    W -= takenWeight;
    time += takenWeight;

    printf("Selected item %d: weight = %.2f, fraction = %.2f\n",
           items[best].id, takenWeight,
           items[best].fraction);
}

printf("\nTotal value: %.2f\n", totalValue);
printf("Total weight used: %.2f\n", time);

return 0;


}
