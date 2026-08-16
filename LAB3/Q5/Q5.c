#include <stdio.h>
#include <stdlib.h>

/*
    Special Pattern Matrix:

        | A B |
    M = | B A |

    The same structure exists recursively
    until a single element is reached.
*/


// Allocate an n x n matrix
int **allocateMatrix(int n) {
    int **mat = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++) {
        mat[i] = (int *)malloc(n * sizeof(int));
    }

    return mat;
}


// Free an n x n matrix
void freeMatrix(int **mat, int n) {
    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }

    free(mat);
}


// Add two n x n matrices
void addMatrix(int **A, int **B, int **C, int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}


// Subtract two n x n matrices
void subtractMatrix(int **A, int **B, int **C, int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}


/*
    Recursive multiplication of special-pattern matrices.

    A and B have the form:

        | A1 A2 |       | B1 B2 |
        | A2 A1 |       | B2 B1 |

    Result C has the form:

        | X Y |
        | Y X |
*/
void specialMultiply(int **A, int **B, int **C, int n) {

    // Base case
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int m = n / 2;

    /*
        Allocate the four blocks:

        A1 = A11
        A2 = A12

        B1 = B11
        B2 = B12
    */

    int **A1 = allocateMatrix(m);
    int **A2 = allocateMatrix(m);

    int **B1 = allocateMatrix(m);
    int **B2 = allocateMatrix(m);


    // Extract A1, A2, B1, B2
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {

            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + m];

            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + m];
        }
    }


    /*
        P = (A1 + A2)(B1 + B2)

        Q = (A1 - A2)(B1 - B2)
    */

    int **Aplus = allocateMatrix(m);
    int **Bplus = allocateMatrix(m);

    int **Aminus = allocateMatrix(m);
    int **Bminus = allocateMatrix(m);

    addMatrix(A1, A2, Aplus, m);
    addMatrix(B1, B2, Bplus, m);

    subtractMatrix(A1, A2, Aminus, m);
    subtractMatrix(B1, B2, Bminus, m);


    // P and Q
    int **P = allocateMatrix(m);
    int **Q = allocateMatrix(m);

    /*
        Only TWO recursive multiplications
    */
    specialMultiply(Aplus, Bplus, P, m);
    specialMultiply(Aminus, Bminus, Q, m);


    /*
        X = (P + Q) / 2
        Y = (P - Q) / 2
    */

    int **X = allocateMatrix(m);
    int **Y = allocateMatrix(m);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {

            X[i][j] = (P[i][j] + Q[i][j]) / 2;
            Y[i][j] = (P[i][j] - Q[i][j]) / 2;
        }
    }


    /*
        Construct result:

             | X Y |
        C =  | Y X |
    */

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {

            C[i][j] = X[i][j];

            C[i][j + m] = Y[i][j];

            C[i + m][j] = Y[i][j];

            C[i + m][j + m] = X[i][j];
        }
    }


    // Free allocated memory

    freeMatrix(A1, m);
    freeMatrix(A2, m);

    freeMatrix(B1, m);
    freeMatrix(B2, m);

    freeMatrix(Aplus, m);
    freeMatrix(Bplus, m);

    freeMatrix(Aminus, m);
    freeMatrix(Bminus, m);

    freeMatrix(P, m);
    freeMatrix(Q, m);

    freeMatrix(X, m);
    freeMatrix(Y, m);
}


// Print matrix
void printMatrix(int **A, int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", A[i][j]);
        }

        printf("\n");
    }
}


int main() {

    int n;

    printf("Enter n (power of 2): ");
    scanf("%d", &n);

    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);


    printf("\nEnter Matrix A:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }


    printf("\nEnter Matrix B:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }


    // Multiply using Divide and Conquer
    specialMultiply(A, B, C, n);


    printf("\nResult Matrix:\n");
    printMatrix(C, n);


    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}