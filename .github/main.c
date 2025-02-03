#include <stdio.h> // printf_s, scanf_s, gets
#include <string.h> // memset, memcpy
#include <stdbool.h> // bool
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
			unsigned subQuantities[maxSegments];
			memset(subQuantities, 0, sizeof(unsigned) * numSegments); // clear out the interesting part of the array
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
	if(argc<2){
		printf_s("Usage: %s [-q] <segment lengths filename>\n", argv[0]);
		return 1;
	}
	
	bool quiet = false;
	if(argv[1][0]=='-' && argv[1][1]=='q' && argv[1][2]=='\0'){
		quiet = true;
		if(argc<3){
			printf_s("Usage: %s [-q] <segment lengths filename>\n", argv[0]);
			return 1;
		}
	}
	
	const char* pFilename = quiet ? argv[2]: argv[1]; // filename is argv[2] if -q is present else argv[1]
	FILE* pFile = NULL;
	if (fopen_s(&pFile, pFilename, "r") != 0)
	{
		printf_s("Error opening file %s\n", pFilename);
		return 1;
	}

	unsigned length, value, numSegments = 0;
	segment segments[maxSegments]; // not ideal, but good enough?
	char strBuffer[256];
	
	while ((fgets(strBuffer, sizeof(strBuffer), pFile) != NULL) && (numSegments < maxSegments))
	{
		if (strBuffer[0]=='#'){
			continue;
		}
		if (sscanf_s(strBuffer, "%u, %u", &length, &value) != 2)
		{
			printf_s("Error reading segment %u\n", numSegments);
			return 1;
		}
		// add length and value to collection.  Fixed size array?  Linked list?
		segments[numSegments].length = length;
		segments[numSegments].value = value;
		numSegments++;
	}
	fclose(pFile);

#ifdef DEBUG
	printf_s("Read %u segments.\n", numSegments);
    for (unsigned seg = 0; seg < numSegments; ++seg)
	{
		printf_s("Length: %u, Value: %u\n", segments[seg].length, segments[seg].value);
	}
#endif
	unsigned rem;
	unsigned quantities[maxSegments];
	unsigned suppliedRodLength = 0;
	if(!quiet){
		printf_s("Enter rod length: ");
	}
	int numScanned;
	while ((fgets(strBuffer, sizeof(strBuffer), stdin)) != NULL){
		numScanned = sscanf_s(strBuffer, "%u", &suppliedRodLength);

		if (numScanned != 1 || strBuffer[0] == '-'){
			printf_s("Invalid input: %s\n", strBuffer);
		}
		else{
			// printf_s("Rod length: %u\n", suppliedRodLength);
			value = splitRod(suppliedRodLength, numSegments, segments, &rem, quantities);

			

			printf_s("{\n"); // {
			printf_s("\"input_length\": %u,\n", suppliedRodLength); // "input_length": rodlength,
			printf_s("\"value\": %u,\n", value); // "value": totalValue,
			printf_s("\"remainder\": %u,\n", rem); // "remainder": remainder,
			printf_s("\"cuts\": [\n"); // "cuts": [
			for (unsigned seg = 0; seg < numSegments; ++seg)
			{
				// printf_s("%u @ %u = %u\n", quantities[seg], segments[seg].length, quantities[seg]*segments[seg].value);

				printf_s("{ \"length\": %u, \"count\": %u,\n", segments[seg].length, quantities[seg]); // { "length": lengthOfPiece, "count": numToCut,
				printf_s("\"piece_value\": %u, \"value\": %u}", segments[seg].value, quantities[seg]*segments[seg].value); // "piece_value": val, "value": totalValueForLength},
				if(seg<numSegments-1){
					printf_s(",");
				}
				printf_s("\n");
			}
			printf_s("] }\n"); // ] }
			



			//printf_s("Remainder: %u\n", rem);
			//printf_s("Value: %u\n", value);
		}

		if(!quiet){
			printf_s("Enter rod length: ");
		}
	}
	
}