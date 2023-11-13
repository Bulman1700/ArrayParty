#ArrayParty

ArrayParty is a unique data structure alternative to a static 2D array. It stores array 'fragments' inside an integer pointer array on an 'as-needed' basis.
When these array fragments are no longer needed, we deallocate the array fragment, thus saving space rather than having an empty array bloat the data structure.

Advantages: Reduces amount of unused memory being wasted. Uses get(), set(), and delete() functions to access and modify individual elements of the ArrayParty. 
(See ArrayParty.h for a list of funcional prototypes).
