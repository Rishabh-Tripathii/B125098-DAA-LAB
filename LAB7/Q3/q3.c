#include <stdio.h>

#define MAX 50

long long dp[MAX];
int split[MAX];

/*
    Standard 3-peg Tower of Hanoi.

    Move n disks from source to destination
    using auxiliary peg.
*/
void hanoi3(int n, int source, int destination, int auxiliary)
{
    if (n == 0)
        return;

    hanoi3(n - 1, source, auxiliary, destination);

    printf("Move disk %d: Peg %d -> Peg %d\n",
           n, source, destination);

    hanoi3(n - 1, auxiliary, destination, source);
}


/*
    4-peg Tower of Hanoi.

    This function uses the optimal split stored
    in split[n].
*/
void hanoi4(int n, int source, int destination,
            int auxiliary1, int auxiliary2)
{
    if (n == 0)
        return;

    if (n == 1)
    {
        printf("Move disk 1: Peg %d -> Peg %d\n",
               source, destination);
        return;
    }

    int k = split[n];

    /*
        Step 1:
        Move k smallest disks from source
        to auxiliary1 using 4 pegs.
    */
    hanoi4(k,
           source,
           auxiliary1,
           destination,
           auxiliary2);

    /*
        Step 2:
        Move remaining n-k disks using
        the normal 3-peg algorithm.

        auxiliary1 contains the k smaller disks,
        so it cannot be used.
    */
    hanoi3(n - k,
           source,
           destination,
           auxiliary2);

    /*
        Step 3:
        Move the k smaller disks from auxiliary1
        to destination.
    */
    hanoi4(k,
           auxiliary1,
           destination,
           source,
           auxiliary2);
}


int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n < 1 || n >= MAX)
    {
        printf("Invalid number of disks.\n");
        return 1;
    }

    /*
        Base cases
    */
    dp[0] = 0;
    dp[1] = 1;

    /*
        Dynamic programming
    */
    for (int i = 2; i <= n; i++)
    {
        dp[i] = 999999999;

        /*
            Try every possible split k.
        */
        for (int k = 1; k < i; k++)
        {
            long long moves =
                2 * dp[k]
                + ((1LL << (i - k)) - 1);

            if (moves < dp[i])
            {
                dp[i] = moves;
                split[i] = k;
            }
        }
    }

    printf("\nMinimum number of moves = %lld\n",
           dp[n]);

    printf("\nSequence of moves:\n\n");

    /*
        Pegs:
        1 = source
        2 = auxiliary
        3 = auxiliary
        4 = destination
    */
    hanoi4( n, 1, 4, 2, 3 );

    return 0;
}