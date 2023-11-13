// Johnathon Bulman

// Test.c
// ======
// A test of various stat-related functions for an array party.
// Capacity (33,000 total elements).


#include <stdio.h>
#include <stdlib.h>
#include "ArrayParty.h"

int main(void)
{
	AP *data = createArrayParty(1100, 30);

	// Set a few elements.
	// index, key (one key only).
	set(data, 10, 5);
	set(data, 11, 23);
	set(data, 997, 25);
	set(data, 885, 23);
	set(data, 2, 11);
	set(data, -1, 5); // invalid
	set(data, 73, 22);
	set(data, 419, 68);

	printIfValid(data, 72477);   // invalid
	printIfValid(data, 885);     // 23
	printIfValid(data, -1);      // invalid
	printIfValid(data, 419);     // 68
	printIfValid(data, 73);      // 22
	printIfValid(data, 100);     // invalid
	
	

	// Print some stats.
	printf("Size: %d\n", getSize(data));
	printf("Capacity: %d\n", getCapacity(data));
	printf("Allocated Cells: %d\n", getAllocatedCellCount(data));
	printf("Traditional Array Size: %llu bytes\n", getArraySizeInBytes(data));
	printf("Lonely Party Array Size: %llu bytes\n", getCurrentSizeInBytes(data));

	destroyArrayParty(data);

	return 0;
}
