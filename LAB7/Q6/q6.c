#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int year;
    int type;       // +1 = birth, -1 = death
} Event;

/*
 * Sort by year.
 * If two events occur in the same year,
 * death (-1) must come before birth (+1).
 */
int compareEvents(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->year != e2->year)
        return e1->year - e2->year;

    // Death before birth
    return e1->type - e2->type;
}

int main()
{
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    Event *events = malloc(2 * n * sizeof(Event));

    if (events == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter birth year and death year for each scientist:\n");

    for (int i = 0; i < n; i++) {
        int birth, death;

        scanf("%d %d", &birth, &death);

        events[2 * i].year = birth;
        events[2 * i].type = +1;

        events[2 * i + 1].year = death;
        events[2 * i + 1].type = -1;
    }

    // Sort all events
    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int alive = 0;
    int maxAlive = 0;
    int bestYear = 0;

    for (int i = 0; i < 2 * n; i++) {

        alive += events[i].type;

        if (alive > maxAlive) {
            maxAlive = alive;
            bestYear = events[i].year;
        }
    }

    printf("\nMaximum number of scientists alive = %d\n", maxAlive);
    printf("Time/year when maximum occurs = %d\n", bestYear);

    free(events);

    return 0;
}