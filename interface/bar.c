#include <stdio.h>

void print_bars(int bars[8])
{
    int i, j, k;
    int display[8][8];
    for (i = 0; i < 8; i++)
    {
        j = 0;
        k = 0;

        for (j = 0; j < bars[i]; j++)
            display[7-j][i] = 1;

        display[7-j][i] = 0;
        
        for (k = bars[i]+1; k < 8; k++)
            display[7-k][i] = -1;  
    }

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (display[i][j] == 1)
                printf("| | ");
            else if (display[i][j] == 0)
                printf("___ ");
            else
                printf("    ");
        }
        printf("\n");
    }
}

int main()
{
    int bars[8];
    bars[0] = 1;
    bars[1] = 5;
    bars[2] = 3;
    bars[3] = 7;
    bars[4] = 4;
    bars[5] = 5;
    bars[6] = 1;
    bars[7] = 3;

    print_bars(bars);

    return 0;
}

/*
___ ___
| | | |

*/
