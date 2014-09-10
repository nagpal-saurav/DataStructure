//
//  CArray.h
//  CArray
//
//  Created by Saurav Nagpal on 1/15/14.
//  Copyright (c) 2013 $aur@v Nagp@l.
//

#ifndef CArray_CArray_h
#define CArray_CArray_h

enum carray_type_enum{
    array_int,
    array_float,
    array_double,
    array_string,
    array_void // if specify then memory handling at developer end
};

typedef enum carray_type_enum   carray_type;
typedef struct carray_struct    carray;

/*-------------------------------------------- newArray-----
 |  Function newArray
 |
 |  Purpose:  Create and return the new array refrence.
 |
 |  Parameters:
 |	carray_type (IN)   -- type of array
 |
 |  Returns:  refrence of the newly created array
 *-------------------------------------------------------------------*/
carray* newArray(carray_type type);
/*-------------------------------------------- newArrayWithElements-----
 |  Function newArrayWithElements
 |
 |  Purpose:  Create and return the new array refrence with the given elements.
 |
 |  Parameters:
 |	carray_type (IN)    --  type of array
 |  void*   (IN)        --  list of elements to be inserted
 |
 |  Returns:  refrence of the newly created array
 *-------------------------------------------------------------------*/
carray* newArrayWithElements(carray_type type, void* elements);

#endif
