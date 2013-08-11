// do not change this code except in the following ways:
//   * write code for the following functions:
//      * bigOrSmallEndian()
//      * getNextFloat()
//      * printNumberData()
//   * change studentName by changing "I. Forgot" to your actual name

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static char *studentName = "Randall Sewell";


// Pre-condition: None
// Post-condition: None
// report whether machine is big or small endian
// Code adapted from Endianness White Paper (Intel 2004)
// 
void bigOrSmallEndian()
{	
	union {
		char Array[4];
		long Chars;
	} TestUnion;
	int 	x;
	char 	c = 'a';

	for (x = 0; x < 4; x++) {
		TestUnion.Array[x] = c++;
	}
	if (TestUnion.Chars == 0x61626364) {
		printf("byte order: big-endian\n\n");
	} else if (TestUnion.Chars == 0x64636261) {
		printf("byte order: little-endian\n\n");
	} else {
		printf("byte order check has failed\n\n");
	}
}

// get next float using scanf()
// returns 1 (success) or 0 (failure)
// if call succeeded, return float value via f pointer
int getNextFloat(float *f)
{

	const int 		bias = 127;
	const int		base = 2;
	unsigned int 	hex = 0;
	int 			binArray[32] = {0}; 
	int 			bitIndex = 0;
	int 			i = 0;
	int 			sign = 0;
	int 			exponent = 0;
	float 			mantissa = 1;
	float 			test = 0;

	// Reads input in hexadecimal format
	scanf("%x", &hex);

	// Converts hex input to binary array
	// I'm not 100% confident this would work the same on a big-endian system, 
	// but I also don't have any way to test that
	for (bitIndex = 0; bitIndex < 32; bitIndex++)
	{
		binArray[bitIndex] = hex % 2;
		hex = hex / 2;
		printf("%i", binArray[bitIndex]);
	}
	
	// Calculates the true exponent, which is the power to which 2 is raised
	i = 7;
	for (bitIndex = 30; bitIndex > 22; bitIndex--)
	{
		if (binArray[bitIndex]) {
			exponent = exponent + pow(base, i);
		}
		i--;
	}

	// Special case for denormalized numbers
	// Exponent bitfield of all zeros; non-zero fraction field
	if (exponent == 0 && *f != 0) {
		mantissa = 0;
		exponent = 1;
	}
	exponent = exponent - bias;
	
	// Calculates the mantissa, or fractional portion
	i=1;
	for (bitIndex = 22; bitIndex > -1; bitIndex--)
	{
		if (binArray[bitIndex]) {
			mantissa = mantissa + 1/(pow(base, i));
		}
		i++;
	}

	// Set the sign
	if (!binArray[31]) {
		sign = 1;
	} else {
		sign = -1;
	}

	// Sets the float value of f*
	// I'm not clear why, but directly assigning *f without the intermediate variable 
	// did't work properly
	test = (sign * pow(base,exponent) * mantissa);
	*f = test;
	
	printf("\nExponent: ");
	printf("%i", exponent);
	printf("\nMantissa: ");
	printf("%e", mantissa);
	printf("\n");

	printf("Is your numbers: ");
	printf("%e", f);
	printf("\n");
	
	return 1;                               // in C, a zero value means false, anything else means true
}


// print requested data for the given number
void printNumberData(float f)
{	

	unsigned int 	hex = (*(int *)&f);
	const int 		bias = 127;
	const int 		base = 2;
	int 			binArray[32] = {0}; //Bool
	int 			bitIndex = 0;
	int 			i = 0;
	int 			sign = 0;
	int 			exponent = 0;
	int				fracBits = 0;
	int 			denorm = 0;
	int 			inf = 0;
	int 			qnan = 0;
	int				snan = 0;
	float 			mantissa = 1;
	

	// Converts hex input to binary array
	// I'm not 100% confident this would work the same on a big-endian system, 
	// but I also don't have any way to test that
	for (bitIndex = 0; bitIndex < 32; bitIndex++)
	{
		binArray[bitIndex] = hex % 2;
		hex = hex / 2;
	}

	// Calculates the true exponent, which is the power to which 2 is raised
	i = 7;
	for (bitIndex = 30; bitIndex > 22; bitIndex--)
	{
		if (binArray[bitIndex]) {
			exponent = exponent + pow(base, i);
		}
		i--;
	}

	// Special case for denormalized numbers
	// Exponent bitfield of all zeros; non-zero fraction field
	if (exponent == 0 && f != 0) {
		mantissa = 0;
		exponent = 1;
		denorm = 1;
	}
	exponent = exponent - bias;
	
	// Calculates the mantissa, or fractional portion
	i=1;
	for (bitIndex = 22; bitIndex > -1; bitIndex--)
	{
		if (binArray[bitIndex]) {
			mantissa = mantissa + 1/(pow(base, i));
			fracBits = fracBits + pow(base, i);
		}
		i++;
	}

	// Displays the common representation of the sign
	//printf("\nSign: ");
	if (!binArray[31]) {
		//printf("+");
		sign = 1;
	} else {
		//printf("-");
		sign = -1;
	}

	// SPECIAL CASES
	
	// Infinity; Sign derived previously
	if (exponent == 128 && mantissa == 1.0) {
		inf = 1;
	}
	
	// NaN(s)
	if (exponent == 128 && mantissa != 1.0) {
		if (binArray[22]) {
			qnan = 1;
		} else {
			snan = 1;
		}
	}
		
	
	
	
	printf("0x%08X", *(int *)&f);
	printf("\nsignBit ");
	printf("%i", binArray[31]);
	printf(", expBits ");
	printf("%i", exponent + bias);
	printf(", fracBits ");
	printf("0x%08X", fracBits);
	if (denorm) {
		printf("\ndenormalized: exp = ");
		printf("%i", exponent * sign);
	}
	
	printf("\nExponent: ");
	printf("%i", exponent);
	printf("\nMantissa: ");
	printf("%e", mantissa);
	printf("\n");

	printf("Is your numbers: ");
	printf("%e", f);
	printf("\n");

	printf("Is your hex: ");
	
	printf("\n");
}

// do not change this function in any way
int main(int argc, char **argv)
{
    float   f;                              // number currently being analyzed
    int     nValues;                        // number of values successfully parsed by scanf

    printf("CS201 - A01 - %s\n\n", studentName);
    bigOrSmallEndian();
    for (;;) {
        if (argc == 1)                      // allow grading script to control ...
            printf("> ");                   // ... whether prompt character is printed
        nValues = getNextFloat(&f);
        if (! nValues) {                    // encountered bad input
            printf("bad input\n");
            while (getchar() != '\n') ;     // flush bad line from input buffer
            continue;
            }
        printNumberData(f);
        if (f == 0.0)
            break;
        }
    printf("\n");
    return 0;
}
