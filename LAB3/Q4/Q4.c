#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for an n x n matrix
int** allocateMatrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }

    return matrix;
}

// Function to free allocated matrix memory
void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

// Add two matrices: C = A + B
void add(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Subtract two matrices: C = A - B
void subtract(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's Matrix Multiplication
void strassen(int** A, int** B, int** C, int n) {

    // Base Case: 1x1 matrix
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    // Allocate submatrices of A
    int** A11 = allocateMatrix(k);
    int** A12 = allocateMatrix(k);
    int** A21 = allocateMatrix(k);
    int** A22 = allocateMatrix(k);

    // Allocate submatrices of B
    int** B11 = allocateMatrix(k);
    int** B12 = allocateMatrix(k);
    int** B21 = allocateMatrix(k);
    int** B22 = allocateMatrix(k);

    // Allocate submatrices of C
    int** C11 = allocateMatrix(k);
    int** C12 = allocateMatrix(k);
    int** C21 = allocateMatrix(k);
    int** C22 = allocateMatrix(k);

    // Allocate P1 to P7
    int** P1 = allocateMatrix(k);
    int** P2 = allocateMatrix(k);
    int** P3 = allocateMatrix(k);
    int** P4 = allocateMatrix(k);
    int** P5 = allocateMatrix(k);
    int** P6 = allocateMatrix(k);
    int** P7 = allocateMatrix(k);

    // Temporary matrices
    int** T1 = allocateMatrix(k);
    int** T2 = allocateMatrix(k);

    // Divide A and B into 4 submatrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {

            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // P1 = (A11 + A22) * (B11 + B22)
    add(A11, A22, T1, k);
    add(B11, B22, T2, k);
    strassen(T1, T2, P1, k);

    // P2 = (A21 + A22) * B11
    add(A21, A22, T1, k);
    strassen(T1, B11, P2, k);

    // P3 = A11 * (B12 - B22)
    subtract(B12, B22, T2, k);
    strassen(A11, T2, P3, k);

    // P4 = A22 * (B21 - B11)
    subtract(B21, B11, T2, k);
    strassen(A22, T2, P4, k);

    // P5 = (A11 + A12) * B22
    add(A11, A12, T1, k);
    strassen(T1, B22, P5, k);

    // P6 = (A21 - A11) * (B11 + B12)
    subtract(A21, A11, T1, k);
    add(B11, B12, T2, k);
    strassen(T1, T2, P6, k);

    // P7 = (A12 - A22) * (B21 + B22)
    subtract(A12, A22, T1, k);
    add(B21, B22, T2, k);
    strassen(T1, T2, P7, k);

    // C11 = P1 + P4 - P5 + P7
    add(P1, P4, T1, k);
    subtract(T1, P5, T2, k);
    add(T2, P7, C11, k);

    // C12 = P3 + P5
    add(P3, P5, C12, k);

    // C21 = P2 + P4
    add(P2, P4, C21, k);

    // C22 = P1 - P2 + P3 + P6
    subtract(P1, P2, T1, k);
    add(T1, P3, T2, k);
    add(T2, P6, C22, k);

    // Combine C11, C12, C21, C22 into C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {

            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    // Free memory
    freeMatrix(A11, k);
    freeMatrix(A12, k);
    freeMatrix(A21, k);
    freeMatrix(A22, k);

    freeMatrix(B11, k);
    freeMatrix(B12, k);
    freeMatrix(B21, k);
    freeMatrix(B22, k);

    freeMatrix(C11, k);
    freeMatrix(C12, k);
    freeMatrix(C21, k);
    freeMatrix(C22, k);

    freeMatrix(P1, k);
    freeMatrix(P2, k);
    freeMatrix(P3, k);
    freeMatrix(P4, k);
    freeMatrix(P5, k);
    freeMatrix(P6, k);
    freeMatrix(P7, k);

    freeMatrix(T1, k);
    freeMatrix(T2, k);
}

// Function to print matrix
void printMatrix(int** matrix, int n) {

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {
            printf("%d\t", matrix[i][j]);
        }

        printf("\n");
    }
}

// Function to check whether n is a power of 2
int isPowerOfTwo(int n) {

    if (n <= 0)
        return 0;

    return (n & (n - 1)) == 0;
}

int main() {

    int n;

    // Take matrix size from user
    printf("Enter the size of the square matrices: ");
    scanf("%d", &n);

    // Check valid matrix size
    if (!isPowerOfTwo(n)) {
        printf("\nError: Matrix size must be a power of 2.\n");
        printf("Valid sizes are: 2, 4, 8, 16, 32, ...\n");
        return 1;
    }

    // Allocate matrices
    int** A = allocateMatrix(n);
    int** B = allocateMatrix(n);
    int** C = allocateMatrix(n);

    // Input Matrix A
    printf("\nEnter elements of Matrix A:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            printf("A[%d][%d] = ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    // Input Matrix B
    printf("\nEnter elements of Matrix B:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            printf("B[%d][%d] = ", i, j);
            scanf("%d", &B[i][j]);
        }
    }

    // Display Matrix A
    printf("\nMatrix A:\n");
    printMatrix(A, n);

    // Display Matrix B
    printf("\nMatrix B:\n");
    printMatrix(B, n);

    // Perform Strassen Matrix Multiplication
    strassen(A, B, C, n);

    // Display result
    printf("\nResultant Matrix C (A x B):\n");
    printMatrix(C, n);

    // Free allocated memory
    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}