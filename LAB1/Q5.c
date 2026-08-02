#include <stdio.h>

int findTransitionPoint(int arr[], int n)
{
    int low = 0;
    int high = n - 1;
    int ans = -1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == 1)
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return ans;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter array elements (0s followed by 1s):\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int transition = findTransitionPoint(arr, n);

    if (transition == -1)
        printf("No transition point found.\n");
    else
        printf("Transition Point = %d\n", transition);

    return 0;
}