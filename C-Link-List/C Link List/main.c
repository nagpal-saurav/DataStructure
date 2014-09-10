//
//  main.c
//  C Link List
//
//  Created by Saurav Nagpal on 12/24/13.
//  Copyright (c) 2013 $aur@v Nagp@l.
//

#include "LinkList.h"
#include <stdio.h>

void createFloatLinkList(link_list* list);
void createIntegerLinkList(link_list* list);
void createDoubleLinkList(link_list* list);
void createStringLinkList(link_list* list);
void traverseCallback(long index, void* data);

int main(int argc, const char * argv[])
{
    link_list* int_list = newLinkList(link_list_int);
    link_list* float_list = newLinkList(link_list_float);
    link_list* double_list = newLinkList(link_list_double);
    link_list* string_list = newLinkList(link_list_string);
    int elementValue_int = 0;
    float elementValue_float = 0.0;
    double elementValue_double = 0.000;
    char* elementValue_String = NULL;
    createIntegerLinkList(int_list);
    createFloatLinkList(float_list);
    createDoubleLinkList(double_list);
    createStringLinkList(string_list);
    
    getElementAtIndex(int_list, 2, &elementValue_int);
    getElementAtIndex(float_list, 3, &elementValue_float);
    getElementAtIndex(double_list, 4, &elementValue_double);
    getElementAtIndex(string_list, 4, &elementValue_String);
    
    printf("intValue:%d\n",elementValue_int);
    printf("floatValue:%f\n",elementValue_float);
    printf("doubleValue:%f\n",elementValue_double);
    printf("stringValue:%s\n",elementValue_String);
    
    deleteElementAtIndexInLinkList(int_list, 2);
    deleteElementAtIndexInLinkList(float_list, 3);
    deleteElementAtIndexInLinkList(double_list, 4);
    deleteElementAtIndexInLinkList(string_list, 4);
    
    getElementAtIndex(int_list, 2, &elementValue_int);
    getElementAtIndex(float_list, 3, &elementValue_float);
    getElementAtIndex(double_list, 4, &elementValue_double);
    getElementAtIndex(string_list, 4, &elementValue_String);
    printf("intValue:%d\n",elementValue_int);
    printf("floatValue:%f\n",elementValue_float);
    printf("doubleValue:%f\n",elementValue_double);
    printf("stringValue:%s\n",elementValue_String);
    
    traverseList(int_list, traverseCallback);
    
    releaseLinkList(&int_list);
    releaseLinkList(&float_list);
    releaseLinkList(&double_list);
    releaseLinkList(&string_list);
    
    return 0;
}

//Sample create a link list int
void createIntegerLinkList(link_list* list){
    int value = 2;
    int loopCount = 0;
    int loopLimit = 5;
    while(loopCount < loopLimit){
        addElementInLinkList(list, &value);
        value += loopLimit;
        loopCount++;
    }
}

void createFloatLinkList(link_list* list){
    float value = 5.0;
    float increment = 9.0;
    int loopCount = 0;
    int loopLimit = 5;
    while(loopCount < loopLimit){
        addElementInLinkList(list, &value);
        value += increment;
        loopCount++;
    }
}

void createDoubleLinkList(link_list* list){
    double value = 5.0000;
    double increment = 9.00000;
    int loopCount = 0;
    int loopLimit = 5;
    while(loopCount < loopLimit){
        addElementInLinkList(list, &value);
        value += increment;
        loopCount++;
    }
}

void createStringLinkList(link_list* list){
    char string_link[5][10] ={
      "Sample",
        "link",
        "list",
        "Array",
        "Char"
    };
    int loopCount = 0;
    int loopLimit = 5;
    while(loopCount < loopLimit){
        addElementInLinkList(list, &string_link[loopCount]);
        loopCount++;
    }
}

void traverseCallback(long index, void* data){
    int* elementValue = (int*)data;
    printf("%d\n",*elementValue);
}