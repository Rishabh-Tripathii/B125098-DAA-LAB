#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int eggDrop(int E, int F)
{
    /*
        dp[e][f] =
        minimum number of drops needed
        with e eggs and f floors.
    */

    int **dp = malloc((E + 1) * sizeof(int *));

    for (int e = 0; e <= E; e++)
        dp[e] = malloc((F + 1) * sizeof(int));


    /*
        Base cases
    */

    // 0 floors -> 0 drops
    for (int e = 1; e <= E; e++)
        dp[e][0] = 0;

    // 1 floor -> 1 drop
    for (int e = 1; e <= E; e++)
        dp[e][1] = 1;

    // 1 egg -> f drops
    for (int f = 0; f <= F; f++)
        dp[1][f] = f;


    /*
        Fill DP table
    */

    for (int e = 2; e <= E; e++)
    {
        for (int f = 2; f <= F; f++)
        {
            dp[e][f] = INF;

            /*
                Try dropping the egg from
                every possible floor x.
            */

            for (int x = 1; x <= f; x++)
            {
                int eggBreaks = dp[e - 1][x - 1];

                int eggSurvives = dp[e][f - x];

                /*
                    Worst-case number of drops
                */

                int worstCase =
                    1 + max(eggBreaks, eggSurvives);

                dp[e][f] =
                    min(dp[e][f], worstCase);
            }
        }
    }

    int answer = dp[E][F];


    /*
        Free memory
    */

    for (int e = 0; e <= E; e++)
        free(dp[e]);

    free(dp);

    return answer;
}


int main()
{
    int E, F;

    printf("Enter number of eggs: ");
    scanf("%d", &E);

    printf("Enter number of floors: ");
    scanf("%d", &F);

    int result = eggDrop(E, F);

    printf("\nMinimum number of drops = %d\n",
           result);

    return 0;
}