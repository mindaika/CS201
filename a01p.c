// do not change this code except in the following ways:
//   * write code for the following functions:
//      * bigOrSmallEndian()
//      * getNextHexInt()
//      * printNumberData()
//   * change studentName by changing "I. Forgot" to your actual name

#include <stdio.h>
#include <stdlib.h>

static char *studentName = "Randall Sewell";

// report whether machine is big or small endian
void bigOrSmallEndian()
{
  // Unions store data of different types in the same memory location
  union {
    char Array[4];
    long Chars;
  } TestUnion;
  int 	x;
  char 	c = 'a';
  
  // Increments the union array to create an ordered set of values
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

// get next int (entered in hex) using scanf()
// returns 1 (success) or 0 (failure)
// if call succeeded, return int value via i pointer
int getNextHexInt(int *i)
{
  // Reads input in hexadecimal format
  scanf("%x", i);
  return 1;
}

// print requested data for the given number
void printNumberData(int i)
{
  const int 	BIAS = 127;
  unsigned int	hex = i;
  int		binArray[32] = {0};
  int		bitIndex = 0;
  int		index = 0;
  int		sign = 0;
  int		exponent = 0;
  int		expBits = 0;
  int		fracBits = 0;
  int		specialState = -1;
	
  // Converts hex input to binary array
  // I'm not 100% confident this would work the same on a big-endian system, 
  // but I also don't have any way to test that
  for (bitIndex = 0; bitIndex < 32; bitIndex++)
    {
      binArray[bitIndex] = hex % 2;
      hex = hex / 2;
    }

  // Calculates the true exponent, which is the power to which 2 is raised
  index = 7;
  for (bitIndex = 30; bitIndex > 22; bitIndex--)
    {
      exponent = exponent + (binArray[bitIndex] << index);
      index--;
    }
  expBits = exponent;
	
  // Special case for denormalized numbers
  // Exponent bitfield of all zeros; non-zero fraction field
  if (exponent == 0 && i != 0) {
    exponent = 1;
    specialState = 3;
  } else {
    specialState = 4;
  }
  exponent = exponent - BIAS;
	
  // Calculates the mantissa, or fractional portion
  index = 0;
  for (bitIndex = 0; bitIndex < 23; bitIndex++)
    {
      fracBits = fracBits + (binArray[bitIndex] << index);
      index++;
    }

  // Sets the sign
  if (!binArray[31]) {
    sign = 1;
  } else {
    sign = -1;
  }
  
  // SPECIAL CASES
  // Infinity; Sign derived previously
  if (exponent == 128 && fracBits == 0) {
    specialState = 5;
  }
	
  // NaN(s)
  if (exponent == 128 && fracBits != 0) {
    if (binArray[22]) {
      specialState = 1;
    } else {
      specialState = 2;
    }
  }
  
  // Zero(s)
  if (expBits == 0 && fracBits == 0) {
    specialState = 0;
  }

  // Print the signBit, exponent bits, and fraction bits (in hex)
  printf("signBit ");
  printf("%i", binArray[31]);
  printf(", expBits ");
  printf("%3i", expBits);
  printf(", fracBits ");
  printf("0x%08X", fracBits);
  printf("\n");
  
  // Evaluate whether a special case has occurred
  switch (specialState) {
  case 0:
    if (!binArray[31]) {
      printf("+zero");
      printf("\n\n");
    } else {
      printf("-zero");
      printf("\n\n");
      i = 0;
    }
    break;
  case 1:
    printf("QNaN");
    printf("\n\n");
    break;
  case 2:
    printf("SNaN");
    printf("\n\n");
    break;
  case 3:
    printf("denormalized: exp = ");
    printf("%3i", exponent * sign);
    printf("\n\n");
    break;
  case 4:
    printf("normalized:   exp = ");
    printf("%3i", exponent);
    printf("\n\n");
    break;
  case 5:
    if (!binArray[31]) {
      printf("+infinity");
      printf("\n\n");
    } else {
      printf("-infinity");
      printf("\n\n");
    }
    break;
  }
}

// do not change this function in any way
int main(int argc, char **argv)
{
  int     i;                              // number currently being analyzed
  int     nValues;                        // number of values successfully parsed by scanf

  printf("CS201 - A01p - %s\n\n", studentName);
  bigOrSmallEndian();
  for (;;) {
    if (argc == 1)                      // allow grading script to control ...
      printf("> ");                   // ... whether prompt character is printed
    nValues = getNextHexInt(&i);
    printf("0x%08X\n", i);
    if (! nValues) {                    // encountered bad input
      printf("bad input\n");
      while (getchar() != '\n') ;     // flush bad line from input buffer
      continue;
    }
    printNumberData(i);
    if (i == 0)
      break;
  }
  printf("\n");
  return 0;
}
