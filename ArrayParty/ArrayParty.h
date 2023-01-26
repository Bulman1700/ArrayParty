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

ArrayParty *createArrayParty(int num_fragments, int fragment_length);

ArrayParty *destroyArrayParty(ArrayParty *party);

ArrayParty *cloneArrayParty(ArrayParty *party);

ArrayParty *resetArrayParty(ArrayParty *party);

int set(ArrayParty *party, int index, int key);

int get(ArrayParty *party, int index);

int delete(ArrayParty *party, int index);

int containsKey(ArrayParty *party, int key);

int isSet(ArrayParty *party, int index);

int printIfValid(ArrayParty *party, int index);

int getSize(ArrayParty *party);

int getCapacity(ArrayParty *party);

int getAllocatedCellCount(ArrayParty *party);

long long unsigned int getArraySizeInBytes(ArrayParty *party);

long long unsigned int getCurrentSizeInBytes(ArrayParty *party);


#endif
