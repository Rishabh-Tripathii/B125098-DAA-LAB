
#include <stdio.h>
#include <stdlib.h>

#define MAXV 100005
#define MAXE 200005

int parent[MAXV], size[MAXV];
int active[MAXV];
int head[MAXV], to[2 * MAXE], next[2 * MAXE];
long long weight[MAXV], sum[MAXV];
long long ans[MAXV];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

int unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
        return 0;

    if (size[a] < size[b]) {
        int t = a;
        a = b;
        b = t;
    }

    parent[b] = a;
    size[a] += size[b];
    sum[a] += sum[b];
    return 1;
}

int main(void) {
    int V, E;
    scanf("%d %d", &V, &E);

    for (int i = 0; i < V; i++) {
        scanf("%lld", &weight[i]);
        parent[i] = i;
        size[i] = 1;
        active[i] = 0;
        head[i] = -1;
    }

    int edgeU[MAXE], edgeV[MAXE];

    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        edgeU[i] = u;
        edgeV[i] = v;

        to[2 * i] = v;
        next[2 * i] = head[u];
        head[u] = 2 * i;

        to[2 * i + 1] = u;
        next[2 * i + 1] = head[v];
        head[v] = 2 * i + 1;
    }

    int *P = malloc(V * sizeof(int));
    if (P == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < V; i++)
        scanf("%d", &P[i]);

    long long currentMax = 0;

    for (int i = V - 1; i >= 0; i--) {
        int u = P[i];
        active[u] = 1;
        parent[u] = u;
        size[u] = 1;
        sum[u] = weight[u];

        if (sum[u] > currentMax)
            currentMax = sum[u];

        for (int e = head[u]; e != -1; e = next[e]) {
            int v = to[e];

            if (active[v]) {
                int ru = find(u);
                int rv = find(v);

                if (ru != rv) {
                    long long mergedSum = sum[ru] + sum[rv];
                    unite(ru, rv);

                    if (mergedSum > currentMax)
                        currentMax = mergedSum;
                }
            }
        }

        ans[i] = currentMax;
    }

    for (int i = 0; i < V; i++)
        printf("%lld\n", ans[i]);

    free(P);
    return 0;
}
