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

// Returns a new ArrayParty with capacity (num_fragments * fragment_length).
AP *createArrayParty(int num_fragments, int fragment_length);

// Frees the entire ArrayParty.
AP *destroyArrayParty(AP *party);

// Returns a new copy of ArrayParty.
AP *cloneArrayParty(AP *party);

// Resets the ArrayParty.
AP *resetArrayParty(AP *party);

// Inserts 'key' into the specified 'index' inside ArrayParty.
int set(AP *party, int index, int key);

// Retrieves the key at 'index' in ArrayParty.
int get(AP *party, int index);

// Deletes a key at 'index' in ArrayParty.
int delete(AP *party, int index);

// Returns '1' if 'key' is in the ArrayParty.
// Returns '0' otherwise.
int containsKey(AP *party, int key);

// Returns '1' if there is a key at 'index',
// '0' otherwise.
int isSet(AP *party, int index);

// Prints the key at 'index', if it exists.
int printIfValid(AP *party, int index);

// Returns the number of elements in ArrayParty.
int getSize(AP *party);

// Returns maximum number of elements that ArrayParty can hold.
int getCapacity(AP *party);

// Returns maximum number of elements ArrayParty can hold 
// without allocating any new array fragments.
int getAllocatedCellCount(AP *party);

// Returns ArrayParty size in bytes.
long long unsigned int getArraySizeInBytes(AP *party);

// Returns number of bytes that would be used if a traditional 
// 2D array was used.
long long unsigned int getCurrentSizeInBytes(AP *party);


#endif

