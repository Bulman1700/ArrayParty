## ArrayParty

## Description
============
ArrayParty is a unique data structure alternative to a static 2D array. It stores array 'fragments' inside an integer pointer array on an 'as-needed' basis.
When these array fragments are no longer needed, we deallocate the array fragment, thus saving space rather than having an empty array bloat the data structure.

## To Install and Run
==================
To install ArrayParty, please download the entire **ArrayParty** folder.
To run the **test.c** file, type the following into terminal in the directory in which you downloaded **ArrayParty**:

    --gcc ArrayParty.c test.c
    --./a.out

## How To Use
=============
ArrayParty is pretty simple to use. To initialize a new **ArrayParty** struct pointer: you can use the *createArrayParty(num_fragments, fragment_length)* function. <br \z>
    -- ArrayParty *newParty = createArrayParty(55, 30); <br \z>
'55' is the length of *newParty* (i.e., the number of fragments *newParty* holds). <br \z>
'30' is the length of each fragment in *newParty*. <br \z>

To insert elements into **ArrayParty**, you can use the *set(newParty, index, key)* function, where *index* is on the range of (num_fragments * fragment_length - 1). <br \z>
    -- ArrayParty *party = createArrayParty(3, 12);<br \z>
    -- set(party, 14, 599);<br \z>

The *set()* function allocates the second array fragment in **ArrayParty** and goes to the second index in that array, and places *599* at that index. All other array fragments at this point are still unallocated, as they are not being used. <br \z><br \z>

To get a list of complete supported operations, please check out the *ArrayParty.h* header file.


