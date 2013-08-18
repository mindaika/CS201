#include <stdio.h>
#include <stdlib.h>

// You are only allowed to make changes to this code as specified by the comments in it.

// The code you submit must have these two values.
#define N_TIMES     600000
#define ARRAY_SIZE   10000

int main (void)
{
    double  *array = calloc(ARRAY_SIZE, sizeof(double));
    double  sum = 0;
    int     i;

    // You can add variables between this comment ...
    double *ptr;
    double sum1 = 0;
    double sum2 = 0;
    // ... and this one.

    // Please change 'your name' to your actual name.
    printf("CS201 - Asgmt 4 - Randall Sewell\n");
    for (i = 0; i < N_TIMES; i++) {

    // You can change anything between this comment ...
        sum1 = 0;
        sum2 = 0;
        for (ptr = array; ptr < &array[ARRAY_SIZE]; ptr += 12) {
            sum1 += (*ptr) + *(ptr + 1) + *(ptr + 2) + *(ptr + 3) + *(ptr + 4) + *(ptr + 5);
            sum2 += *(ptr + 6) + *(ptr + 7) + *(ptr + 8) + *(ptr + 9) + *(ptr + 10) + *(ptr + 11);
        }
        sum += sum1 + sum2;		
    // ... and this one. But your inner loop must do the same
    // number of additions as this one does.

    }

    // You can add some final code between this comment ...
    // Final time-check is 6.247s averaged across 5 consecutive runs
    // It's a little higher now, actually, so just ignore that
    // ... and this one.

    return 0;
}
