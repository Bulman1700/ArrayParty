// Johnathon Bulman

// ArrayParty.c
// ============
// Data structure alternative to a static 2D array.

#include "ArrayParty.h"
#include <stdio.h>
#include <stdlib.h>


// Returns a new ArrayParty with capacity: num_fragments * fragment_length.
ArrayParty *createArrayParty(int num_fragments, int fragment_length)
{
  ArrayParty *party;

  if (num_fragments <= 0 || fragment_length <= 0)
    return NULL;

  if ((party = malloc(sizeof(ArrayParty))) == NULL)
    return NULL;

  // Calloc: Clear that sh!t out! All the array fragments 
  // at initialization should be unallocated (i.e., NULL).
  if ((party->fragments = calloc(num_fragments, sizeof(int *))) == NULL)
    return NULL;

  if ((party->fragment_sizes = calloc(num_fragments, sizeof(int))) == NULL)
    return NULL;

  // Initial conditions of ArrayParty
  party->num_fragments = num_fragments;
  party->fragment_length = fragment_length;
  party->size = 0;
  party->num_active_fragments = 0;

  // Status of ArrayParty.
  printf("-> A new ArrayParty has emerged from the void. (capacity: %d, fragments: %d)\n", party->num_fragments * party->fragment_length, party->num_fragments);
  return party;
}

// Frees entire ArrayParty.
ArrayParty *destroyArrayParty(ArrayParty *party)
{
  int i;

  if (party == NULL)
    return NULL;

  for (i = 0; i < party->num_fragments; i++)
    if (party->fragments[i] != NULL)
      free(party->fragments[i]);

  free(party->fragment_sizes);
  free(party->fragments);
  free(party);

  // Status on ArrayParty
  printf("-> The ArrayParty has returned to the void.\n");
  return NULL;
}

// Returns a separate copy of the ArrayParty.
ArrayParty *cloneArrayParty(ArrayParty *party)
{
  ArrayParty *partyClone;
  int i, j;

  if (party == NULL)
    return NULL;

  if ((partyClone = calloc(1, sizeof(ArrayParty))) == NULL)
    return NULL;

  if ((partyClone->fragments = calloc(party->num_fragments, sizeof(int *))) == NULL)
    return NULL;

  if ((partyClone->fragment_sizes = calloc(party->num_fragments, sizeof(int))) == NULL)
    return NULL;

  // Pass parameters to new ArrayParty.
  partyClone->num_fragments = party->num_fragments;
  partyClone->fragment_length = party->fragment_length;

  for (i = 0; i < party->num_fragments; i++)
  {
    if (party->fragments[i] == NULL)
      continue;
    
    else
    {
      if ((partyClone->fragments[i] = malloc(sizeof(int) * party->fragment_length)) == NULL)
        return NULL;
      
      partyClone->num_active_fragments++;
    }

    for (j = 0; j < party->fragment_length; j++)
    {
      partyClone->fragments[i][j] = party->fragments[i][j];
      if (partyClone->fragments[i][j] != UNUSED)
      {
        partyClone->size++;
        partyClone->fragment_sizes[i]++;
      }
    }
  }

  printf("-> Successfully cloned the ArrayParty. (capacity: %d, fragments: %d)\n", partyClone->num_fragments * partyClone->fragment_length, partyClone->num_fragments);
  return partyClone;
}

// Sets 'key' at 'index' in the ArrayParty.
int set(ArrayParty *party, int index, int key)
{
  int fragment, fragmentIndex;

  int upperBound = 0, lowerBound;
  int i;

  if (party == NULL)
  {
    // Status of ArrayParty.
    printf("-> Bloop! NULL pointer detected in set().\n");
    return LPA_FAILURE;
  }

  fragment = getFragment(party, index);
  fragmentIndex = getFragmentIndex(party, index);

  if (out_of_bounds(party, index))
  {
    // Status of ArrayParty.
    printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index, fragment, fragmentIndex);
    return LPA_FAILURE;
  }

  // If the index is being placed in an unallocated fragment, then allocate that fragment.
  if (party->fragments[fragment] == NULL)
  {
    party->fragments[fragment] = malloc(sizeof(int) * party->fragment_length);

    if (party->fragments[fragment] == NULL)
      return LPA_FAILURE;

    party->num_active_fragments++;

    // All cells in newly allocated fragment are 'unused' aside from 
    // the index that 'key' is mapped to.
    for (i = 0; i < party->fragment_length; i++)
      party->fragments[fragment][i] = UNUSED;

    party->fragments[fragment][fragmentIndex] = key;

    // Updating size of newly allocated fragment.
    party->fragment_sizes[fragment]++;

    // Updating total size of the ArrayParty.
    party->size++;

    lowerBound = index - fragmentIndex;
    upperBound = lowerBound + party->fragment_length - 1;

    // Status of ArrayParty
    printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n", fragment, party->fragment_length, lowerBound, upperBound);
  }

  // Preventing duplicate keys.
  else if (party->fragments[fragment][fragmentIndex] == key)
    return LPA_SUCCESS;

  // If array fragment is allocated, place 'key' at index.
  else if (party->fragments[fragment][fragmentIndex] == UNUSED)
  {
    party->fragments[fragment][fragmentIndex] = key;
    party->fragment_sizes[fragment]++;
    party->size++;
  }

  // Replace 'key' at index.
  else
    party->fragments[fragment][fragmentIndex] = key;

  return LPA_SUCCESS;
}

// Retrieves 'key' from the ArrayParty.
int get(ArrayParty *party, int index)
{
  int fragment, fragmentIndex;

  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in get().\n");
    return LPA_FAILURE;
  }

  fragment = getFragment(party, index);
  fragmentIndex = getFragmentIndex(party, index);

  if (out_of_bounds(party, index))
  {
    printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index, fragment, fragmentIndex);
    return LPA_FAILURE;
  }

  if (party->fragments[fragment] == NULL)
    return UNUSED;

  // Return the key.
  return party->fragments[fragment][fragmentIndex];
}

// Deletes 'key' from the ArrayParty.
int delete(ArrayParty *party, int index)
{
  int upperBound = 0, lowerBound = 0;

  int fragment, fragmentIndex;

  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in delete().\n");
    return LPA_FAILURE;
  }

  fragment = getFragment(party, index);
  fragmentIndex = getFragmentIndex(party, index);

  if (out_of_bounds(party, index))
  {
    printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, fragment, fragmentIndex);
    return LPA_FAILURE;
  }

  // If 'key' doesnt exist at the index.
  if (party->fragments[fragment] == NULL || party->fragments[fragment][fragmentIndex] == UNUSED)
    return LPA_FAILURE;

  party->fragments[fragment][fragmentIndex] = UNUSED;
  party->fragment_sizes[fragment]--;
  party->size--;

  // If all cells in fragment are UNUSED, dealloate fragment.
  if (party->fragment_sizes[fragment] == 0)
  {
    free(party->fragments[fragment]);
    party->fragments[fragment] = NULL;
    party->num_active_fragments--;

    lowerBound = index - fragmentIndex;
    upperBound = lowerBound + party->fragment_length - 1;

    // Status of the ArrayParty.
    printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n", fragment, party->fragment_length, lowerBound, upperBound);
  }

  return LPA_SUCCESS;
}

// Linear search for the key.
// Returns 1 if found.
int containsKey(ArrayParty *party, int key)
{
  int i, j;

  for (i = 0; i < party->num_fragments; i++)
    for (j = 0; j < party->fragment_length; j++)
      if (party->fragments[i][j] == key)
        return 1;
  
  // Key not found.
  return 0;
}

// Returns 1 if a key exists at the specified index.
int isSet(ArrayParty *party, int index)
{
  int fragment;
  int fragmentIndex;

  if (party == NULL || out_of_bounds(party, index))
    return 0;

  fragment = getFragment(party, index);
  fragmentIndex = getFragmentIndex(party, index);

  if ((party->fragments[fragment] != NULL) && (party->fragments[fragment][fragmentIndex] != UNUSED))
    return 1;

  return 0;
}

// Prints key at specified index, if it exists.
// If no key exists, quietly fails.
int printIfValid(ArrayParty *party, int index)
{
  // Refers to dimensions of ArrayParty.
  int fragment;
  int fragmentIndex;

  if (party == NULL)
    return LPA_FAILURE;

  fragment = getFragment(party, index);
  fragmentIndex = getFragmentIndex(party, index);
  
  if (out_of_bounds(party, index))
    return LPA_FAILURE;

  if (party->fragments[fragment] == NULL)
    return LPA_FAILURE;

  if (party->fragments[fragment][fragmentIndex] == UNUSED)
    return LPA_FAILURE;

  // Prints found index value to the screen.
  printf("%d\n", party->fragments[fragment][fragmentIndex]);
  return LPA_SUCCESS;
}

// Returns ArrayParty to its initial state.
ArrayParty *resetArrayParty(ArrayParty *party)
{
  int i;
  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in resetArrayParty().\n");
    return party;
  }

  for (i = 0; i < party->num_fragments; i++)
  {
    free(party->fragments[i]);
    party->fragments[i] = NULL;
    party->fragment_sizes[i] = 0;
  }

  party->num_active_fragments = 0;
  party->size = 0;

  printf("-> The ArrayParty has returned to its nascent state. (capacity: %d, fragments: %d)\n", party->num_fragments * party->fragment_length, party->num_fragments);
  return party;
}

// Gets total size of the ArrayParty.
int getSize(ArrayParty *party)
{
  if (party == NULL)
    return -1;

  return party->size;
}

// Gets total capacity of the ArrayParty.
int getCapacity(ArrayParty *party)
{
  if (party == NULL)
    return -1;

  return (party->num_fragments * party->fragment_length);
}

// Gets allocated capacity of the ArrayParty.
int getAllocatedCellCount(ArrayParty *party)
{
  if (party == NULL)
    return -1;

  return (party->num_active_fragments * party->fragment_length);
}

// Returns size (in bytes) of static 2D array with eqivalent data.
long long unsigned int getArraySizeInBytes(ArrayParty *party)
{
  if (party == NULL)
    return 0;

  return (long long unsigned int)(getCapacity(party) * sizeof(int));
}

// Gets total size (int bytes) of the ArrayParty.
long long unsigned int getCurrentSizeInBytes(ArrayParty *party)
{

  if (party == NULL)
    return 0;

  return (long long unsigned int)(sizeof(ArrayParty *) + sizeof(ArrayParty) + (sizeof(int *) * party->num_fragments) + (sizeof(int) * party->num_fragments) + ((party->num_active_fragments * party->fragment_length) * sizeof(int)));

}

// Helper Functions

int getFragment(ArrayParty *party, int index)
{
  return index / party->fragment_length;
}

int getFragmentIndex(ArrayParty *party, int index)
{
  return index % party->fragment_length;
}

int out_of_bounds(ArrayParty *party, int index)
{
  return (index >= (party->num_fragments * party->fragment_length) || index < 0) ? 1 : 0;
}
