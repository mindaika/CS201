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

  // Control Word storage; CW is mem16
  char  *cw2   = malloc(4*sizeof(char));
  short *newCW = malloc(sizeof(short));
  short *oldCW = malloc(sizeof(short));
  int roundingMode = 3 << 10;
  
   // Change Rounding Mode
  asm("fstcw %5;" // store control word in oldCW
	  "mov %5, %4;" // copy control word into cw2
	  "or %2, %4;" // put new mode into rounding control bits
	  "mov %4, %3;" // copy cw2 into newCW
	  "fldcw %3;" // Loads newCW into Control
	  : "=m" (n)
	  : "m" (n), "m" (roundingMode),
		"m" (newCW), "r" (cw2), "m" (oldCW) // mov requires one argument in a register
	  );


  asm("fldl %2;" // Load exponent to ST0
	  "fldl %1;" // Load mantissa to ST0
	  "fyl2x;" // Y*log(2)x -> ST0
	  "fst %%st(1);" // Copy ST0 -> ST1
	  "frndint;" // Round
	  "fxch %%st(1);" // Switch
	  "fsub %%st(1), %%st(0);" // Leave fractional in ST1
	  "f2xm1;" // Discount exponent calculator
	  "fld1;" // Literally the number 1
	  "faddp;" // Added
	  "fscale;" // Compute result
	  "fstp %%st(1);" // Pop ST1
	  "fstpl %0;" // Store final result in n
	  "fldcw %3;" // load the old control word from cw
	  : "=m" (n)
	  : "m" (n), "m" (exp), "m" (oldCW)
	  );

  // Cleanup, aisle7
  oldCW = NULL;
  free (oldCW);

  newCW = NULL;
  free (newCW);

  cw2 = NULL;
  free (cw2);
  return n;

// do not change anything below this comment, except for printing out your name
}

int main(int argc, char **argv)
{
    double  n = 0.0;
    double  exp = 0.0;

    printf("CS201 - Assignment 02sp - Randall Sewell\n");
    if (argc > 1)
        n = atof(argv[1]);
    if (argc > 2)
        exp = atof(argv[2]);

    printf("%.*f to the %.*f = %.*f\n",
           PRECISION, n, PRECISION, exp, PRECISION, powD(n, exp));

    return 0;
}
