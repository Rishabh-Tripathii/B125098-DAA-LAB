#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateArray(int arr[], int n)
{
    for(int i = 0; i < n; i++)
        arr[i] = rand() % 1000;
}

void copyArray(int source[], int dest[], int n)
{
    for(int i = 0; i < n; i++)
        dest[i] = source[i];
}

int bubbleSortOptimized(int arr[], int n)
{
    int comparisons = 0;
    int swapped, temp;

    for(int i = 0; i < n - 1; i++)
    {
        swapped = 0;

        for(int j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if(arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        if(swapped == 0)
            break;
    }

    return comparisons;
}

int bubbleSortNormal(int arr[], int n)
{
    int comparisons = 0;
    int temp;

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if(arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return comparisons;
}

int main()
{
    srand(time(NULL));

    FILE *fp = fopen("comparisons.csv", "w");

    fprintf(fp, "Size,Optimized,Normal\n");

    printf("Size\tOptimized\tNormal\n");

    for(int n = 10; n <= 100; n += 10)
    {
        int arr1[n];
        int arr2[n];

        generateArray(arr1, n);
        copyArray(arr1, arr2, n);

        int c1 = bubbleSortOptimized(arr1, n);
        int c2 = bubbleSortNormal(arr2, n);

        printf("%d\t%d\t\t%d\n", n, c1, c2);

        fprintf(fp, "%d,%d,%d\n", n, c1, c2);
    }

    fclose(fp);

    return 0;
}