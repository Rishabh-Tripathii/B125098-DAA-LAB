
#include <stdio.h>

#define MAX 100005

int parent[MAX], size[MAX];
long long weight[MAX];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int u, int v) {
    int ru = find(u);
    int rv = find(v);

    if (ru == rv)
        return;

    if (size[ru] < size[rv]) {
        int temp = ru;
        ru = rv;
        rv = temp;
    }

    parent[rv] = ru;
    size[ru] += size[rv];
    weight[ru] += weight[rv];
}

int main() {
    int n, m, K;
    scanf("%d %d %d", &n, &m, &K);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &weight[i]);
        parent[i] = i;
        size[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        unite(u, v);

        long long answer = 0;

        for (int j = 0; j < n; j++) {
            if (parent[j] == j && size[j] <= K) {
                if (weight[j] > answer)
                    answer = weight[j];
            }
        }

        printf("%lld\n", answer);
    }

    return 0;
}
