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
    double  arraySum = 0;
    int     arrayFlag = 0;
    // ... and this one.

    // Please change 'your name' to your actual name.
    printf("CS201 - Asgmt 4 - Randall Sewell\n");
    for (i = 0; i < N_TIMES; i++) {
    // You can change anything between this comment ...
        int     j;
        if ( arrayFlag == 0 ) {
            double accum = 0;
            for (j = 0; j < ARRAY_SIZE; j++) {
                accum += array[j];
            }
            arraySum = accum;
            arrayFlag = 1;
        }
        sum += arraySum;
    // ... and this one. But your inner loop must do the same
    // number of additions as this one does.
    }
    // You can add some final code between this comment ...
    printf("You cannot make a thing idiot-proof;\n");
    printf("you can only make it idiot-resistant.\n");
    printf("So long, and thanks for all the fish.\n");
    printf("\nThanks for a great class!\n");
    // ... and this one.
    return 0;
}
