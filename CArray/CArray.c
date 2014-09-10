//
//  CArray.c
//  CArray
//
//  Created by Saurav Nagpal on 1/15/14.
//  Copyright (c) 2013 $aur@v Nagp@l.
//

#include "CArray.h"
#include <stdio.h>
#include <stdlib.h>
/*************************
 *Variable Declaration
 ************************/

/*************************
 *Variable Defination
 ************************/
struct carray_struct{
    void*               array;
    long                count;
    carray_type         array_type;
};

/*************************
 *Function Defination
 ************************/

/*************************
 *Public Methods
 ************************/
//allocate the memory to array
carray* newArray(carray_type type){
    carray* array = (carray*)calloc(sizeof(carray), 1);
    array->array = NULL;
    array->array_type = type;
    array->count = 0;
    return array;
}