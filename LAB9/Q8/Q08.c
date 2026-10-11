#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

// Compare function for sorting
int compare(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
        return -1;
    if (x > y)
        return 1;

    return 0;
}

// Function to find minimum meeting rooms
int minMeetingRooms(int start[], int end[], int n)
{
    int i = 0, j = 0;
    int rooms = 0;
    int maxRooms = 0;

    // Sort start and end times
    qsort(start, n, sizeof(int), compare);
    qsort(end, n, sizeof(int), compare);

    while (i < n)
    {
        // A meeting starts before the earliest meeting ends
        if (start[i] < end[j])
        {
            rooms++;
            i++;

            if (rooms > maxRooms)
                maxRooms = rooms;
        }
        else
        {
            // A meeting has ended, so its room becomes available
            rooms--;
            j++;
        }
    }

    return maxRooms;
}

int main()
{
    int n;
    int start[MAX], end[MAX];

    printf("Enter the number of meetings: ");
    scanf("%d", &n);

    if (n < 0 || n > MAX)
    {
        printf("Invalid number of meetings.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        printf("Enter start and end time of meeting %d: ", i + 1);
        scanf("%d %d", &start[i], &end[i]);

        if (start[i] >= end[i])
        {
            printf("Invalid interval. Start must be less than end.\n");
            return 1;
        }
    }

    if (n == 0)
    {
        printf("Minimum meeting rooms required: 0\n");
        return 0;
    }

    int result = minMeetingRooms(start, end, n);

    printf("\nMinimum meeting rooms required: %d\n", result);

    return 0;
}