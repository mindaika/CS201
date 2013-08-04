// starter file for Assignment 02sp

#include <stdio.h>
#include <stdlib.h>

#define PRECISION   3

// you can define new functions between this comment ...

// ... and this comment. If the new functions are called from powD,
// they must be coded in assembly language.

double powD(double n, double exp)
{
// do not change anything above this comment

    return n;

// do not change anything below this comment, except for printing out your name
}

int main(int argc, char **argv)
{
    double  n = 0.0;
    double  exp = 0.0;

    printf("CS201 - Assignment 02sp - your name\n");
    if (argc > 1)
        n = atof(argv[1]);
    if (argc > 2)
        exp = atof(argv[2]);

    printf("%.*f to the %.*f = %.*f\n",
           PRECISION, n, PRECISION, exp, PRECISION, powD(n, exp));

    return 0;
}
