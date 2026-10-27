#include <stdio.h>
#include <stdlib.h>
typedef struct Edge {
    int to;
    struct Edge *next;
} Edge;
void addEdge(Edge **graph, int u, int v) {
    Edge *e = malloc(sizeof(Edge));

    if (e == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    e->to = v;
    e->next = graph[u];
    graph[u] = e;
}
void multiSourceBFS(
    Edge **graph,
    int V,
    int K,
    int hubs[],
    int R
) {
    int *dist = malloc((size_t)V * sizeof(int));
    int *owner = malloc((size_t)V * sizeof(int));
    int *queue = malloc((size_t)V * sizeof(int));

    if (dist == NULL || owner == NULL || queue == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(dist);
        free(owner);
        free(queue);
        exit(EXIT_FAILURE);
    }

    // Initially, every vertex is unvisited.
    for (int i = 0; i < V; i++) {
        dist[i] = -1;
        owner[i] = -1;
    }

    int front = 0;
    int rear = 0;

    // Insert hubs in increasing index order.
    // hubs[i] is a vertex number; its hub index is i + 1.
    for (int i = 0; i < K; i++) {
        int h = hubs[i];

        if (dist[h] == -1) {
            dist[h] = 0;
            owner[h] = i + 1;
            queue[rear++] = h;
        }
    }

    // Multi-source BFS.
    while (front < rear) {
        int u = queue[front++];

        for (Edge *e = graph[u]; e != NULL; e = e->next) {
            int v = e->to;

            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                owner[v] = owner[u];
                queue[rear++] = v;
            }
        }
    }
    // Apply the radius constraint.
    for (int v = 0; v < V; v++) {
        if (dist[v] == -1 || dist[v] > R) {
            owner[v] = -1;
        }
    }
    // Print results.
    printf("\nVertex\tOwner\tNearest Distance\n");
    for (int v = 0; v < V; v++) {
        printf("%d\t%d\t", v, owner[v]);

        if (dist[v] == -1)
            printf("UNREACHABLE\n");
        else
            printf("%d\n", dist[v]);
    }

    free(dist);
    free(owner);
    free(queue);
}

int main(void) {
    int V, E, K, R;

    printf("Enter V, E, K, R:\n");

    if (scanf("%d %d %d %d", &V, &E, &K, &R) != 4 ||
        V <= 0 || E < 0 || K <= 0 || K > V || R < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    Edge **graph = calloc((size_t)V, sizeof(*graph));

    int *hubs = malloc((size_t)K * sizeof(int));

    if (graph == NULL || hubs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(graph);
        free(hubs);
        return 1;
    }

    printf("Enter the undirected edges (u v):\n");

    for (int i = 0; i < E; i++) {
        int u, v;

        if (scanf("%d %d", &u, &v) != 2 ||
            u < 0 || u >= V || v < 0 || v >= V) {
            printf("Invalid edge.\n");
            return 1;
        }

        addEdge(graph, u, v);
        addEdge(graph, v, u);
    }

    printf("Enter the K hub vertices in index order:\n");

    for (int i = 0; i < K; i++) {
        if (scanf("%d", &hubs[i]) != 1 ||
            hubs[i] < 0 || hubs[i] >= V) {
            printf("Invalid hub vertex.\n");
            return 1;
        }

        // A vertex cannot represent two different indexed hubs.
        for (int j = 0; j < i; j++) {
            if (hubs[j] == hubs[i]) {
                printf("Hub vertices must be distinct.\n");
                return 1;
            }
        }
    }

    multiSourceBFS(graph, V, K, hubs, R);

    // Free graph memory.
    for (int i = 0; i < V; i++) {
        Edge *e = graph[i];

        while (e != NULL) {
            Edge *temp = e;
            e = e->next;
            free(temp);
        }
    }

    free(graph);
    free(hubs);

    return 0;
}
