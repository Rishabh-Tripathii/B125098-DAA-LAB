#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MAX_STEPS 1000000

/* Perform and display the Collatz trajectory of n */
void analyzeTrajectory(uint64_t n)
{
    uint64_t current = n;
    uint64_t maximum = n;
    uint64_t steps = 0;

    printf("\nTrajectory for %" PRIu64 ":\n", n);
    printf("%" PRIu64, current);

    while (current != 1 && steps < MAX_STEPS)
    {
        /*
            Even case:
                n -> n / 2
        */
        if (current % 2 == 0)
        {
            current /= 2;
        }
        /*
            Odd case:
                n -> 3n + 1

            Check for overflow before multiplication.
        */
        else
        {
            if (current > (UINT64_MAX - 1) / 3)
            {
                printf("\nOverflow detected for %" PRIu64 "\n", current);
                return;
            }

            current = 3 * current + 1;
        }

        if (current > maximum)
            maximum = current;

        steps++;

        printf(" -> %" PRIu64, current);
    }

    if (steps >= MAX_STEPS)
    {
        printf("\nMaximum step limit reached.");
        return;
    }

    printf("\n\nNumber of steps : %" PRIu64, steps);
    printf("\nMaximum value   : %" PRIu64, maximum);
    printf("\n");
}


/* Analyze every starting value in the interval [a,b] */
void analyzeInterval(uint64_t a, uint64_t b)
{
    uint64_t current;
    uint64_t steps;
    uint64_t maximum;

    uint64_t longestStart = a;
    uint64_t longestSteps = 0;

    uint64_t highestStart = a;
    uint64_t highestValue = 0;

    printf("\nCollatz Analysis for interval [%" PRIu64 ", %" PRIu64 "]\n",
           a, b);

    printf("\n%-15s %-15s %-20s\n",
           "Starting Value", "Steps", "Maximum Value");

    printf("------------------------------------------------------\n");

    for (uint64_t start = a; start <= b; start++)
    {
        current = start;
        steps = 0;
        maximum = start;

        while (current != 1 && steps < MAX_STEPS)
        {
            if (current % 2 == 0)
            {
                current /= 2;
            }
            else
            {
                if (current > (UINT64_MAX - 1) / 3)
                {
                    printf("%-15" PRIu64 " Overflow\n", start);
                    break;
                }

                current = 3 * current + 1;
            }

            if (current > maximum)
                maximum = current;

            steps++;
        }

        if (steps < MAX_STEPS && current == 1)
        {
            printf("%-15" PRIu64 " %-15" PRIu64 " %-20" PRIu64 "\n",
                   start, steps, maximum);

            /* Find trajectory with maximum number of steps */
            if (steps > longestSteps)
            {
                longestSteps = steps;
                longestStart = start;
            }

            /* Find trajectory reaching the highest value */
            if (maximum > highestValue)
            {
                highestValue = maximum;
                highestStart = start;
            }
        }
    }

    printf("\nLongest trajectory:\n");
    printf("Starting value : %" PRIu64 "\n", longestStart);
    printf("Number of steps: %" PRIu64 "\n", longestSteps);

    printf("\nHighest value reached:\n");
    printf("Starting value : %" PRIu64 "\n", highestStart);
    printf("Maximum value  : %" PRIu64 "\n", highestValue);
}


int main()
{
    uint64_t n;
    uint64_t a, b;

    printf("Enter starting value n: ");
    scanf("%" SCNu64, &n);

    if (n < 1)
    {
        printf("Starting value must be >= 1.\n");
        return 1;
    }

    printf("Enter interval [a,b]:\n");

    printf("a = ");
    scanf("%" SCNu64, &a);

    printf("b = ");
    scanf("%" SCNu64, &b);

    if (a < 1 || b < a)
    {
        printf("Invalid interval. Require 1 <= a <= b.\n");
        return 1;
    }

    /* Analyze the user-provided starting value */
    analyzeTrajectory(n);

    /* Analyze all starting values in [a,b] */
    analyzeInterval(a, b);

    return 0;
}