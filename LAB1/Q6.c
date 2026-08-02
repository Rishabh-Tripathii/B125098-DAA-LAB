#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];

    srand(time(NULL));

    printf("\nGenerated Array:\n");

    for(int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }

    qsort(arr, n, sizeof(int), compare);

    int duplicate = 0;

    for(int i = 0; i < n - 1; i++)
    {
        if(arr[i] == arr[i + 1])
        {
            duplicate = 1;
            break;
        }
    }

    if(duplicate)
        printf("\n\nDuplicate elements are present.\n");
    else
        printf("\n\nAll elements are unique.\n");

    return 0;
}