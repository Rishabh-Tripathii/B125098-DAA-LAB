
#include <stdio.h>
#include <stdlib.h>

int *parent, *size;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v)
        return;

    if (size[u] < size[v]) {
        int temp = u;
        u = v;
        v = temp;
    }

    parent[v] = u;
    size[u] += size[v];
}

int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int main(void) {
    int n, m;

    scanf("%d %d", &n, &m);

    int *A = malloc(n * sizeof(int));
    int *result = malloc(n * sizeof(int));
    parent = malloc(n * sizeof(int));
    size = malloc(n * sizeof(int));

    if (!A || !result || !parent || !size) {
        printf("Memory allocation failed\n");
        free(A);
        free(result);
        free(parent);
        free(size);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        parent[i] = i;
        size[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unite(u, v);
    }

    int **indices = malloc(n * sizeof(int *));
    int **values = malloc(n * sizeof(int *));
    int *count = calloc(n, sizeof(int));

    if (!indices || !values || !count) {
        printf("Memory allocation failed\n");
        free(A);
        free(result);
        free(parent);
        free(size);
        free(indices);
        free(values);
        free(count);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        indices[i] = malloc(n * sizeof(int));
        values[i] = malloc(n * sizeof(int));

        if (!indices[i] || !values[i]) {
            printf("Memory allocation failed\n");
            for (int j = 0; j <= i; j++) {
                free(indices[j]);
                free(values[j]);
            }
            free(indices);
            free(values);
            free(count);
            free(A);
            free(result);
            free(parent);
            free(size);
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        int root = find(i);
        indices[root][count[root]] = i;
        values[root][count[root]] = A[i];
        count[root]++;
    }

    for (int root = 0; root < n; root++) {
        if (count[root] == 0)
            continue;

        qsort(indices[root], count[root], sizeof(int), compare);
        qsort(values[root], count[root], sizeof(int), compare);

        for (int j = 0; j < count[root]; j++)
            result[indices[root][j]] = values[root][j];
    }

    printf("Lexicographically smallest permutation:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", result[i]);
    printf("\n");

    for (int i = 0; i < n; i++) {
        free(indices[i]);
        free(values[i]);
    }

    free(indices);
    free(values);
    free(count);
    free(A);
    free(result);
    free(parent);
    free(size);

    return 0;
}
