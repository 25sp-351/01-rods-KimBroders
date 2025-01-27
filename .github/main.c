#include <stdio.h> // printf, scanf_s
#include <string.h> // memset, memcpy
#include <stdlib.h> // atoi
#define maxSegments 100U

typedef struct segment segment;
struct segment
{
    unsigned length;
    unsigned value;
};

// split the Rod; returns total value; also update *pRem with remainder and cuts with number of cuts of each size
// recursive implementation; try each cut that will fit and recurse to cut the remainder.  Select the highest value cut…
unsigned splitRod(const unsigned rodLength, const unsigned numSegments, const segment segments[], unsigned *pRem, unsigned quantities[])
{
	unsigned maxValue = 0;
	memset(quantities, 0, sizeof(unsigned) * numSegments);
    *pRem = rodLength;
	for (unsigned seg = 0U; seg < numSegments; ++seg)
	{
		if (rodLength >= segments[seg].length)
		{
            unsigned rem;
			unsigned subQuantities[maxSegments] = {0};
			unsigned value = segments[seg].value + splitRod(rodLength - segments[seg].length, numSegments, segments, &rem, subQuantities);
			if (value > maxValue)
			{
				maxValue = value;
				*pRem = rem;
				memcpy(quantities, subQuantities, sizeof(unsigned) * numSegments);
				quantities[seg] += 1;
			}
		}
	}
	return maxValue;
}

int main(int argc, char*argv[])
{
	unsigned suppliedRodLength = atoi(argv[1]);
	
	unsigned length, value, numSegments = 0;
	segment segments[maxSegments]; // not ideal, but good enough?
	while ((scanf_s("%u, %u", &length, &value) != EOF) && (numSegments < maxSegments))
	{
		// add length and value to collection.  Fixed size array?  Linked list?
		segments[numSegments].length = length;
		segments[numSegments].value = value;
		numSegments++;
	}
#ifdef DEBUG
	printf("Read %u segments.\n", numSegments);
    for (unsigned seg = 0; seg < numSegments; ++seg)
	{
		printf("Length: %u, Value: %u\n", segments[seg].length, segments[seg].value);
	}
#endif
	unsigned rem;
	unsigned quantities[maxSegments] = {0};
	
	value = splitRod(suppliedRodLength, numSegments, segments, &rem, quantities);
	
	for (unsigned seg = 0; seg < numSegments; ++seg)
	{
		printf("%u @ %u = %u\n", quantities[seg], segments[seg].length, quantities[seg]*segments[seg].value);
	}
	printf("Remainder: %u\n", rem);
	printf("Value: %u\n", value);
}