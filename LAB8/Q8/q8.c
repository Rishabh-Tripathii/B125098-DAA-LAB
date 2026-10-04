#include <stdio.h>
#include <float.h>

#define MAX 100

double cost[MAX][MAX];
double weight[MAX][MAX];
int root[MAX][MAX];

double p[MAX];
double q[MAX];

void printTree(int i, int j, int parent, char side)
{
    if (i > j)
    {
        if (parent != -1)
            printf("d%d is the %s child of k%d\n",
                   j, side, parent);

        return;
    }

    int r = root[i][j];

    if (parent == -1)
        printf("k%d is the root\n", r);
    else
        printf("k%d is the %s child of k%d\n",
               r, side, parent);

    printTree(i, r - 1, r, 'L');
    printTree(r + 1, j, r, 'R');
}

int main()
{
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("\nEnter successful search probabilities p[1..%d]:\n", n);

    for (int i = 1; i <= n; i++)
        scanf("%lf", &p[i]);

    printf("\nEnter unsuccessful search probabilities q[0..%d]:\n", n);

    for (int i = 0; i <= n; i++)
        scanf("%lf", &q[i]);

    /*
        Base cases:
        cost[i][i-1] represents an empty subtree.
    */
    for (int i = 1; i <= n + 1; i++)
    {
        cost[i][i - 1] = q[i - 1];
        weight[i][i - 1] = q[i - 1];
    }

    /*
        Compute OBST using Dynamic Programming.
    */
    for (int length = 1; length <= n; length++)
    {
        for (int i = 1; i <= n - length + 1; i++)
        {
            int j = i + length - 1;

            weight[i][j] =
                weight[i][j - 1] + p[j] + q[j];

            cost[i][j] = DBL_MAX;

            for (int r = i; r <= j; r++)
            {
                double currentCost =
                    cost[i][r - 1] +
                    cost[r + 1][j] +
                    weight[i][j];

                if (currentCost < cost[i][j])
                {
                    cost[i][j] = currentCost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum Expected Search Cost = %.4lf\n",
           cost[1][n]);

    printf("\nOptimal Binary Search Tree:\n");

    printTree(1, n, -1, ' ');

    return 0;
}