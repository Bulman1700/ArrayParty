#ifndef __ArrayParty_H
#define __ArrayParty_H


// Directives and Definitions

#include <limits.h>

#define UNUSED INT_MIN
#define LPA_SUCCESS -1911318925
#define LPA_FAILURE -1911318926

typedef struct ArrayParty
{
	int size;                  // number of occupied cells across all fragments
	int num_fragments;         // number of fragments (arrays) in this struct
	int fragment_length;       // number of cells per fragment
	int num_active_fragments;  // number of allocated (non-NULL) fragments
	int **fragments;           // array of pointers to individual fragments
	int *fragment_sizes;       // stores number of used cells in each fragment
} ArrayParty;

typedef ArrayParty AP;


// Functional Prototypes

AP *createArrayParty(int num_fragments, int fragment_length);

AP *destroyArrayParty(AP *party);

AP *cloneArrayParty(AP *party);

AP *resetArrayParty(AP *party);

int set(AP *party, int index, int key);

int get(AP *party, int index);

int delete(AP *party, int index);

int containsKey(AP *party, int key);

int isSet(AP *party, int index);

int printIfValid(AP *party, int index);

int getSize(AP *party);

int getCapacity(AP *party);

int getAllocatedCellCount(AP *party);

long long unsigned int getArraySizeInBytes(AP *party);

long long unsigned int getCurrentSizeInBytes(AP *party);


#endif

