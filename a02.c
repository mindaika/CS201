// starter file for Assignment 02

#include <stdio.h>
#include <stdlib.h>

#define PRECISION   3

double absD(double n)
{
// do not change anything above this comment

  asm("pushl %ebp;"
	  "movl %esp, %ebp;"
	  "fld 8(%ebp);"
	  "fabs;"
	  "fstp 8(%ebp);"
	  "popl %ebp;"
	  );
  return n;

// do not change anything below this comment, except for printing out your name
}

int main(int argc, char **argv)
{
    double  n = 0;

    printf("CS201 - Assignment 02 - Randall Sewell\n");
    if (argc > 1)
        n = atof(argv[1]);

    printf("abs(%.*f) = %.*f\n", PRECISION, n, PRECISION, absD(n));

    return 0;
}
