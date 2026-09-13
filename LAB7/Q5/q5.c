#include <stdio.h>

#define MAX 1000

void printPossible(int possible[], int n)
{
    printf("{ ");

    for (int i = 1; i <= n; i++)
    {
        if (possible[i])
            printf("%d ", i);
    }

    printf("}");
}

int main()
{
    int n;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n <= 1 || n >= MAX)
    {
        printf("Invalid input.\n");
        return 1;
    }

    /*
        possible[i] = 1 means that the target
        could currently be at position i.
    */

    int possible[MAX] = {0};
    int next[MAX] = {0};

    /*
        Initially the target can be anywhere.
    */
    for (int i = 1; i <= n; i++)
        possible[i] = 1;

    int shots = 0;

    printf("\nInitial possible positions: ");
    printPossible(possible, n);
    printf("\n\n");


    /*
        Special case: n = 2
    */
    if (n == 2)
    {
        int sequence[] = {1, 1};

        for (int s = 0; s < 2; s++)
        {
            int shot = sequence[s];

            shots++;

            printf("Shot %d -> position %d\n",
                   shots, shot);

            /*
                Target at shot position is hit.
                Remove it from possible positions.
            */
            possible[shot] = 0;

            /*
                If no possible position remains,
                target is guaranteed to be hit.
            */
            int remaining = 0;

            for (int i = 1; i <= n; i++)
            {
                if (possible[i])
                    remaining++;
            }

            if (remaining == 0)
                break;

            /*
                Move every surviving target
                to an adjacent position.
            */
            for (int i = 1; i <= n; i++)
                next[i] = 0;

            for (int i = 1; i <= n; i++)
            {
                if (possible[i])
                {
                    if (i > 1)
                        next[i - 1] = 1;

                    if (i < n)
                        next[i + 1] = 1;
                }
            }

            for (int i = 1; i <= n; i++)
                possible[i] = next[i];

            printf("Possible positions after movement: ");
            printPossible(possible, n);
            printf("\n\n");
        }
    }

    /*
        General case: n > 2
    */
    else
    {
        /*
            First sweep:
            2, 3, 4, ..., n-1
        */
        for (int shot = 2; shot <= n - 1; shot++)
        {
            shots++;

            printf("Shot %d -> position %d\n",
                   shots, shot);

            /*
                Target at shot position is hit.
                Remove it from possible positions.
            */
            possible[shot] = 0;

            /*
                Check whether all possibilities
                have been eliminated.
            */
            int remaining = 0;

            for (int i = 1; i <= n; i++)
            {
                if (possible[i])
                    remaining++;
            }

            if (remaining == 0)
                break;

            /*
                Move target to an adjacent position.
            */
            for (int i = 1; i <= n; i++)
                next[i] = 0;

            for (int i = 1; i <= n; i++)
            {
                if (possible[i])
                {
                    if (i > 1)
                        next[i - 1] = 1;

                    if (i < n)
                        next[i + 1] = 1;
                }
            }

            for (int i = 1; i <= n; i++)
                possible[i] = next[i];

            printf("Possible positions: ");
            printPossible(possible, n);
            printf("\n\n");
        }


        /*
            Second sweep:
            n-1, n-2, ..., 2
        */
        for (int shot = n - 1;
             shot >= 2;
             shot--)
        {
            shots++;

            printf("Shot %d -> position %d\n",
                   shots, shot);

            possible[shot] = 0;

            /*
                Check whether target is guaranteed
                to have been hit.
            */
            int remaining = 0;

            for (int i = 1; i <= n; i++)
            {
                if (possible[i])
                    remaining++;
            }

            if (remaining == 0)
                break;

            /*
                Move surviving targets.
            */
            for (int i = 1; i <= n; i++)
                next[i] = 0;

            for (int i = 1; i <= n; i++)
            {
                if (possible[i])
                {
                    if (i > 1)
                        next[i - 1] = 1;

                    if (i < n)
                        next[i + 1] = 1;
                }
            }

            for (int i = 1; i <= n; i++)
                possible[i] = next[i];

            printf("Possible positions: ");
            printPossible(possible, n);
            printf("\n\n");
        }
    }


    /*
        Final result
    */
    int remaining = 0;

    for (int i = 1; i <= n; i++)
    {
        if (possible[i])
            remaining++;
    }

    printf("--------------------------------\n");

    if (remaining == 0)
    {
        printf("Target is GUARANTEED to be hit.\n");
        printf("Total shots = %d\n", shots);
    }
    else
    {
        printf("Target is NOT guaranteed to be hit.\n");
    }

    return 0;
}