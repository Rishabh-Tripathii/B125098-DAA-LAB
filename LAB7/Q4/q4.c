#include <stdio.h>

#define MAX 100

int sw[MAX];
long long moves = 0;

/* Print switches from left to right */
void printState(int n)
{
    for (int i = n - 1; i >= 0; i--)
        printf("%d ", sw[i]);

    printf("\n");
}

/* Toggle switch i, where 0 = rightmost */
void toggle(int i, int n)
{
    sw[i] = !sw[i];
    moves++;

    printf("Move %lld: switch %d\n", moves, i + 1);
    printf("        ");
    printState(n);
}

/*
    CLEAR(m):

    Starting state of switches 0..m-1:

        1 0 0 ... 0

    ending state:

        0 0 0 ... 0

    The recursive sequence is:

        CLEAR(m-1)
        toggle(m)
        CLEAR(m-1)
*/
void clearSwitches(int m, int n)
{
    if (m == 1)
    {
        toggle(0, n);
        return;
    }

    clearSwitches(m - 1, n);

    toggle(m - 1, n);

    clearSwitches(m - 1, n);
}

/*
    SOLVE(n):

    Starting with the first n switches ON,
    turn all n switches OFF.
*/
void solve(int n, int total)
{
    if (n == 0)
        return;

    if (n == 1)
    {
        toggle(0, total);
        return;
    }

    if (n == 2)
    {
        toggle(1, total);
        toggle(0, total);
        return;
    }

    /*
        1. Solve switches 1 ... n-2.
    */
    solve(n - 2, total);

    /*
        Now state is:

        1 1 0 0 ... 0
        ↑ ↑
        n n-1

        Therefore switch n can be toggled.
    */
    toggle(n - 1, total);

    /*
        Now state is:

        0 1 0 0 ... 0

        Clear switches 1 ... n-1.
    */
    clearSwitches(n - 1, total);
}

int main()
{
    int n;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX)
    {
        printf("Invalid number of switches.\n");
        return 1;
    }

    /* Initially all switches are ON */
    for (int i = 0; i < n; i++)
        sw[i] = 1;

    printf("\nInitial state:\n");
    printState(n);

    printf("\nMoves:\n");

    solve(n, n);

    printf("\nFinal state:\n");
    printState(n);

    printf("\nTotal moves performed = %lld\n", moves);

    return 0;
}