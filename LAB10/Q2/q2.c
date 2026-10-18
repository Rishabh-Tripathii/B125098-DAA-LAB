
#include <stdio.h>
#include <stdlib.h>

int *parent, *size;

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

int unite(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a == b)
        return 0;

    if (size[a] < size[b])
    {
        int temp = a;
        a = b;
        b = temp;
    }

    parent[b] = a;
    size[a] += size[b];

    return 1;
}

int main()
{
    int R, C, K;
    int r, c, id, nr, nc, nid;
    int islands = 0;
    int i, j;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    printf("Enter rows, columns and operations: ");
    scanf("%d %d %d", &R, &C, &K);

    if (R <= 0 || C <= 0 || K < 0 ||
        (long long)R * C > 10000000)
    {
        printf("Invalid input\n");
        return 1;
    }

    int total = R * C;

    parent = malloc(total * sizeof(int));
    size = malloc(total * sizeof(int));

    if (parent == NULL || size == NULL)
    {
        printf("Memory allocation failed\n");
        free(parent);
        free(size);
        return 1;
    }

    for (i = 0; i < total; i++)
    {
        parent[i] = -1;
        size[i] = 0;
    }

    for (i = 0; i < K; i++)
    {
        printf("Enter land coordinates (row column): ");
        scanf("%d %d", &r, &c);

        if (r < 0 || r >= R || c < 0 || c >= C)
        {
            printf("Invalid coordinates\n");
            i--;
            continue;
        }

        id = r * C + c;

        if (parent[id] != -1)
        {
            printf("Islands after operation %d: %d\n",
                   i + 1, islands);
            continue;
        }

        parent[id] = id;
        size[id] = 1;
        islands++;

        for (j = 0; j < 4; j++)
        {
            nr = r + dr[j];
            nc = c + dc[j];

            if (nr >= 0 && nr < R && nc >= 0 && nc < C)
            {
                nid = nr * C + nc;

                if (parent[nid] != -1)
                {
                    if (unite(id, nid))
                        islands--;
                }
            }
        }

        printf("Islands after operation %d: %d\n",
               i + 1, islands);
    }

    free(parent);
    free(size);

    return 0;
}
