#include "stdafx.h"

// Function to return the only odd occurring element
int findOdd(int arr[], int n)
{
	int res = 0, i;
	for (i = 0; i < n; i++)
	{
		res ^= arr[i];
	}
	return res;
}


int Add(int x, int y)
{
	// Iterate till there is no carry  
	while (y != 0)
	{
		// carry now contains common set bits of x and y
		int carry = x & y;

		// Sum of bits of x and y where at least one of the bits is not set
		x = x ^ y;

		// Carry is shifted by one so that adding it to x gives the required sum
		y = carry << 1;
	}
	return x;
}

int Add1(int x, int y)
{
	if (y == 0)
		return x;
	else
		return Add1(x ^ y, (x & y) << 1);
}

int subtract(int x, int y)
{
	// Iterate till there is no carry
	while (y != 0)
	{
		// borrow contains common set bits of y and unset
		// bits of x
		int borrow = (~x) & y;

		// Subtraction of bits of x and y where at least
		// one of the bits is not set
		x = x ^ y;

		// Borrow is shifted by one so that subtracting it from
		// x gives the required sum
		y = borrow << 1;
	}
	return x;
}

int subtract1(int x, int y)
{
	if (y == 0)
		return x;
	return subtract1(x ^ y, (~x & y) << 1);
}

unsigned int countOnes(unsigned int num)
{
	unsigned int total_ones = 0;
	while (num != 0)
	{
		num = num & (num - 1);
		total_ones++;
	}
	return total_ones;
	/*int bits = 0;
	int mask = 1;
	for (int i = 0; i < 32; i++) 
	{
		if ((n & mask) != 0) 
		{
			bits++;
		}
		mask <<= 1;
	}
	return bits;*/
}

// A utility function to count set bits
// in a number x
unsigned int countSetBitsUtil(unsigned int x);

// Returns count of set bits present in all
// numbers from 1 to n
unsigned int countSetBits(unsigned int n)
{
	int bitCount = 0; // initialize the result

	for (int i = 1; i <= n; i++)
		bitCount += countSetBitsUtil(i);

	return bitCount;
}

// A utility function to count set bits 
// in a number x
unsigned int countSetBitsUtil(unsigned int x)
{
	if (x <= 0)
		return 0;
	return (x % 2 == 0 ? 0 : 1) + countSetBitsUtil(x / 2);
}

// Function to swap even
// and odd bits
unsigned int swapBits(unsigned int x)
{
	// Get all even bits of x
	unsigned int even_bits = x & 0xAAAAAAAA;

	// Get all odd bits of x
	unsigned int odd_bits = x & 0x55555555;

	even_bits >>= 1;  // Right shift even bits
	odd_bits <<= 1;   // Left shift odd bits

	return (even_bits | odd_bits); // Combine even and odd bits
}

int isPowerOfTwo(unsigned n)
{
	return n && (!(n & (n - 1)));
}

// Returns position of the only set bit in 'n'
int findPosition(unsigned n)
{
	if (!isPowerOfTwo(n))
		return -1;

	unsigned count = 0;

	// One by one move the only set bit to right till it reaches end
	while (n)
	{
		n = n >> 1;

		// increment count of shifts
		++count;
	}

	return count;
}

int floorAvg(int x, int y)
{
	return (x + y) >> 1;
}

/*unsigned int swapBitsInPair(unsigned int x)
{
	// Extracting the high bit shift it to lowbit
	// Extracting the low bit shift it to highbit
	return ((x & 0b10101010) >> 1) |
		((x & 0b01010101) << 1);
}*/

long computeXOR(const int n)
{
	// Modulus operator are expensive on most of the 
	// computers. n & 3 will be equivalent to n % 4.   

	switch (n & 3) // n % 4 
	{
	case 0: return n;     // if n is multiple of 4
	case 1: return 1;     // If n % 4 gives remainder 1  
	case 2: return n + 1; // If n % 4 gives remainder 2    
	case 3: return 0;     // If n % 4 gives remainder 3  
	}
}