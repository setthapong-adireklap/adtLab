#include <stdio.h>

void romanNum(int num)
{
    int check = num;
    int numArr[7] = {1000, 500, 100, 50, 10, 5, 1};
    char sign[7] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};

    int i, j, n;
    for (i = 0; i < 7; i++)
    {
        if (check / numArr[i] > 0)
        {
            n = check / numArr[i];
            if (n == 4 && i % 2 == 0)
            {
                printf("%c%c", sign[i], sign[i - 1]);
                check %= 4 * numArr[i];
            }
            else if (check / numArr[i + 1] == 9 && i % 2 != 0)
            {
                printf("%c%c", sign[i + 1], sign[i - 1]);
                check %= 9 * numArr[i + 1];
            }
            else
            {
                for (j = 0; j < n; j++)
                {
                    printf("%c", sign[i]);
                }
                check %= numArr[i];
            }
        }
    }
    printf("\n");
}

int main()
{

    int i, n;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        int temp;
        scanf("%d", &temp);
        romanNum(temp);
    }

    return 0;
}