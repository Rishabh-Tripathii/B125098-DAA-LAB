
#include <stdio.h>

void toh(int n, char l, char m, char r, int *cnt)
{
    if (n == 1)
    {
        printf("Move disk 1 from %c to %c\n", l, r);
        (*cnt)++;
        return;
    }

    toh(n - 1, l, r, m, cnt);
    printf("Move disk %d from %c to %c\n", n, l, r);
    (*cnt)++;
    toh(n - 1, m, l, r, cnt);
}

int main()
{
    int n, cnt = 0;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    toh(n, 'A', 'B', 'C', &cnt);

    printf("Total number of moves = %d\n", cnt);

    return 0;
}