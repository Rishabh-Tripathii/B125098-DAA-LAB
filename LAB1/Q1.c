#include <stdio.h>
#include <math.h>

struct func_data {
    char name[30];
    double value;
};

int main()
{
    double n;

    printf("Enter a large value of n: ");
    scanf("%lf", &n);

    double logn = log2(n);

    struct func_data list[] = {
        {"1/n", -logn},
        {"log2(n)", log2(logn)},
        {"12*sqrt(n)", log2(12) + 0.5 * logn},
        {"50*sqrt(n)", log2(50) + 0.5 * logn},
        {"n^0.51", 0.51 * logn},
        {"2^32*n", 32 + logn},
        {"n*log2(n)", logn + log2(logn)},
        {"n^2-324", 2 * logn},
        {"100n^2+6n", log2(100) + 2 * logn},
        {"2n^3", 1 + 3 * logn},
        {"n^(log2 n)", logn * logn},
        {"3^n", n * log2(3)}
    };

    int size = sizeof(list) / sizeof(list[0]);

    struct func_data temp;

    for(int i = 0; i < size - 1; i++)
    {
        for(int j = 0; j < size - i - 1; j++)
        {
            if(list[j].value > list[j + 1].value)
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }

    printf("\nIncreasing order of growth:\n\n");

    for(int i = 0; i < size; i++)
    {
        printf("%d. %s\n", i + 1, list[i].name);
    }

    return 0;
}