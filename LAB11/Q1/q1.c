#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INF (LLONG_MAX / 4)

typedef struct Edge {
    int to;
    int weight;
    struct Edge *next;
} Edge;

typedef struct Node {
    int vertex;
    int parity;
    long long distance;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Deque;

void addEdge(Edge **graph, int u, int v, int w) {
    Edge *e = (Edge *)malloc(sizeof(Edge));

    if (e == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    e->to = v;
    e->weight = w;
    e->next = graph[u];
    graph[u] = e;
}

void pushFront(Deque *dq, int v, int p, long long d) {
    Node *n = (Node *)malloc(sizeof(Node));

    if (n == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    n->vertex = v;
    n->parity = p;
    n->distance = d;
    n->next = dq->front;
    dq->front = n;

    if (dq->rear == NULL)
        dq->rear = n;
}

void pushBack(Deque *dq, int v, int p, long long d) {
    Node *n = (Node *)malloc(sizeof(Node));

    if (n == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    n->vertex = v;
    n->parity = p;
    n->distance = d;
    n->next = NULL;

    if (dq->rear == NULL) {
        dq->front = dq->rear = n;
    } else {
        dq->rear->next = n;
        dq->rear = n;
    }
}

int popFront(Deque *dq, int *v, int *p, long long *d) {
    if (dq->front == NULL)
        return 0;

    Node *n = dq->front;

    *v = n->vertex;
    *p = n->parity;
    *d = n->distance;

    dq->front = n->next;

    if (dq->front == NULL)
        dq->rear = NULL;

    free(n);
    return 1;
}

void shortestPath(Edge **graph, int V, int S, long long C) {
    long long (*dist)[2] =
        malloc((size_t)V * sizeof(*dist));

    if (dist == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < V; i++) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }

    Deque dq = {NULL, NULL};

    // Initially, zero weight-1 edges have been traversed.
    dist[S][0] = 0;
    pushFront(&dq, S, 0, 0);

    int u, parity;
    long long d;

    while (popFront(&dq, &u, &parity, &d)) {

        // Ignore outdated deque entries.
        if (d != dist[u][parity])
            continue;

        for (Edge *e = graph[u]; e != NULL; e = e->next) {
            int v = e->to;
            int w = e->weight;

            // Weight 1 flips parity; weight 0 preserves it.
            int newParity = parity ^ w;
            long long newDistance = d + w;

            if (newDistance < dist[v][newParity]) {
                dist[v][newParity] = newDistance;

                if (w == 0)
                    pushFront(&dq, v, newParity, newDistance);
                else
                    pushBack(&dq, v, newParity, newDistance);
            }
        }
    }

    printf("\nMinimum effective costs:\n");

    for (int v = 0; v < V; v++) {
        if (dist[v][0] == INF && dist[v][1] == INF) {
            printf("Vertex %d: UNREACHABLE\n", v);
        } else {
            long long evenCost = dist[v][0];
            long long oddCost =
                (dist[v][1] == INF) ? INF : dist[v][1] + C;

            long long answer =
                (evenCost < oddCost) ? evenCost : oddCost;

            printf("Vertex %d: %lld\n", v, answer);
        }
    }

    // Free the deque if anything remains.
    while (popFront(&dq, &u, &parity, &d))
        ;

    free(dist);
}

int main(void) {
    int V, E, S;
    long long C;

    printf("Enter number of vertices, edges, source, penalty:\n");

    if (scanf("%d %d %d %lld", &V, &E, &S, &C) != 4 ||
        V <= 0 || E < 0 || S < 0 || S >= V || C < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    Edge **graph = calloc((size_t)V, sizeof(*graph));

    if (graph == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter each directed edge: u v weight (0 or 1)\n");

    for (int i = 0; i < E; i++) {
        int u, v, w;

        if (scanf("%d %d %d", &u, &v, &w) != 3 ||
            u < 0 || u >= V ||
            v < 0 || v >= V ||
            (w != 0 && w != 1)) {
            printf("Invalid edge input.\n");
            return 1;
        }

        addEdge(graph, u, v, w);
    }

    shortestPath(graph, V, S, C);

    for (int i = 0; i < V; i++) {
        Edge *e = graph[i];

        while (e != NULL) {
            Edge *temp = e;
            e = e->next;
            free(temp);
        }
    }

    free(graph);
    return 0;
}
