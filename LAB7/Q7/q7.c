#include <stdio.h>
#include <limits.h>

#define MAX 100

long long m[MAX][MAX];
int s[MAX][MAX];

/* Print the optimal parenthesization */
void printOptimalParenthesis(int i, int j)
{
    if (i == j) {
        printf("A%d", i);
        return;
    }

    printf("(");

    printOptimalParenthesis(i, s[i][j]);
    printf(" x ");
    printOptimalParenthesis(s[i][j] + 1, j);

    printf(")");
}

int main()
{
    int n;
    int p[MAX];

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    /*
     * If there are n matrices:
     *
     * A1 = p[0] x p[1]
     * A2 = p[1] x p[2]
     * ...
     * An = p[n-1] x p[n]
     *
     * Therefore, we need n+1 dimensions.
     */
    printf("Enter %d matrix dimensions:\n", n + 1);
    scanf("%d", &p[0]);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
    }

    /* Cost of multiplying one matrix is zero */
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    /*
     * length = length of the matrix chain
     * We consider chains of length 2, 3, ..., n.
     */
    for (int length = 2; length <= n; length++) {

        for (int i = 1; i <= n - length + 1; i++) {

            int j = i + length - 1;

            m[i][j] = LLONG_MAX;

            /*
             * Try every possible split position k.
             *
             * (Ai ... Ak) x (A(k+1) ... Aj)
             */
            for (int k = i; k < j; k++) {

                long long cost =
                    m[i][k] +
                    m[k + 1][j] +
                    (long long)p[i - 1] * p[k] * p[j];

                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum number of scalar multiplications: %lld\n",
           m[1][n]);

    printf("Optimal parenthesization: ");
    printOptimalParenthesis(1, n);
    printf("\n");

    return 0;
}