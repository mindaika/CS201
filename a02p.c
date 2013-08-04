// starter file for Assignment 02p

#include <stdio.h>
#include <stdlib.h>

#define PRECISION           3
#define RND_CTL_BIT_SHIFT   10

// floating point rounding modes: IA-32 Manual, Vol. 1, p. 4-20
typedef enum {
    ROUND_NEAREST_EVEN =    0 << RND_CTL_BIT_SHIFT,
    ROUND_MINUS_INF =       1 << RND_CTL_BIT_SHIFT,
    ROUND_PLUS_INF =        2 << RND_CTL_BIT_SHIFT,
    ROUND_TOWARD_ZERO =     3 << RND_CTL_BIT_SHIFT
} RoundingMode;

double roundD(double n, RoundingMode roundingMode)
{
// do not change anything above this comment
  
    // Control Word storage; CW is mem16
    char  *cw2   = malloc(4*sizeof(char));
	short *newCW = malloc(sizeof(short));
	short *oldCW = malloc(sizeof(short));
	// n = 2.500; // for testing purposes

	// I suspect at least some of this is redundant, but it works
	// If you'd like to critique it, feel free
	// Also, I don't remember if n was set as "0" or "0.0" in main, and D2L
	// is down so I can't check to make sure. I'll delete this sentence if I can check before
	// I turn it in.
    asm("fstcw %5;" // store control word in oldCW
        "mov %5, %4;" // copy control word into cw2
        "or %2, %4;" // put new mode into rounding control bits
		"mov %4, %3;" // copy cw2 into newCW
		"fldcw %3;" // Loads newCW into Control
        "fldl %0;" // load n into st(0)
        "frndint;" // round n
        "fstpl %0;" // load st(0) back into n
        "fldcw %5;" // load the old control word from cw
        : "=m" (n)
        : "m" (n), "m" (roundingMode),
          "m" (newCW), "r" (cw2), "m" (oldCW) // mov requires one argument in a register
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
    double  n = 0;

    printf("CS201 - Assignment 02p - Randall Sewell\n");
    if (argc > 1)
        n = atof(argv[1]);

    printf("roundD even %.*f = %.*f\n",
           PRECISION, n, PRECISION, roundD(n, ROUND_NEAREST_EVEN));
    printf("roundD down %.*f = %.*f\n",
           PRECISION, n, PRECISION, roundD(n, ROUND_MINUS_INF));
    printf("roundD up   %.*f = %.*f\n",
           PRECISION, n, PRECISION, roundD(n, ROUND_PLUS_INF));
    printf("roundD zero %.*f = %.*f\n",
           PRECISION, n, PRECISION, roundD(n, ROUND_TOWARD_ZERO));

    return 0;
}
