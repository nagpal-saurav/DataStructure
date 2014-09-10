//
//  LinkList.C
//  C Link List
//
//  Created by Saurav Nagpal on 12/24/13.
//  Copyright (c) 2013 $aur@v Nagp@l.
//

#include "LinkList.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>


/*************************
 *Variable Declaration
 ************************/
typedef struct list_struct_info list_struct;

/*************************
 *Variable Defination
 ************************/
struct list_struct_info{
    void*              data;
    list_struct*       next;
};

struct link_list_struct_info{
    list_struct*            link_list;
    long                    list_element_count;
    link_list_type          list_type;
};

/*************************
 *Function Declaration
 ************************/
list_struct* newListElement(link_list_type type,void* data);
void setValueFromlist(list_struct* list, link_list_type type, void* value);
void releaseListElement(list_struct** ptrToElement);
short isListElementEqualToValue(list_struct* list, link_list_type type, void* value);

/*************************
 *Function Defination
 ************************/

/*************************
 *Public Methods
 ************************/
//allocate the memory to list
link_list* newLinkList(link_list_type type){
    link_list* newList = (link_list*) calloc(sizeof(link_list), 1);
    newList->link_list = NULL;
    newList->list_element_count = 0;
    newList->list_type = type;
    return newList;
}

//release the link list memory
void releaseLinkList(link_list** ptrToList){
    list_struct* list = (*ptrToList)->link_list;
    list_struct* tmpList = NULL;
    while (list != NULL) {
        tmpList = list->next;
        free(list->data);
        free(list);
        list = tmpList;
    }
    *ptrToList = NULL;
}

//return the element count
long getElementCount(link_list* list){
    return list->list_element_count;
}
//Return the element value at given index.
void getElementAtIndex(link_list* listContainer, long index, void* value){
    list_struct* list = listContainer->link_list;
    long currentElement = 1;
    while (list != NULL) {
        if(currentElement == index){
            setValueFromlist(list, listContainer->list_type,value);
            break;
        }
        list = list->next;
        currentElement++;
    }
}

//add the element to the list
void addElementInLinkList(link_list* listContainer, void* data){
    list_struct* list = listContainer->link_list;
    list_struct* newElement = newListElement(listContainer->list_type, data);
    switch (listContainer->list_element_count) {
        case 0:{
            listContainer->link_list = newElement;
            break;
        }
        default:{
             while (list->next != NULL) {
                 list = list->next;
             }
            list->next = newElement;
            break;
        }
    }
    listContainer->list_element_count++;
}

//Delete a element in a link list
void deleteElementInLinkList(link_list* listContainer, void* data){
    list_struct* list = listContainer->link_list;
    link_list_type type = listContainer->list_type;
    list_struct* tmp = NULL;
    while (list != NULL) {
        if(isListElementEqualToValue(list, type, data)){
            if(tmp == NULL){
                listContainer->link_list = list->next;
            }else{
                if(list->next == NULL){
                    tmp->next = NULL;
                }else{
                    tmp->next = list->next;
                }
            }
            releaseListElement(&list);
            break;
        }
        tmp = list;
        list = list->next;
    }
}

void deleteElementAtIndexInLinkList(link_list* listContainer, long index){
    list_struct* list = listContainer->link_list;
    if(index > listContainer->list_element_count)
        return;
    long currentElement = 1;
    list_struct* tmp = NULL;
    while (list != NULL) {
        if(index == currentElement){
            if(tmp == NULL){
                listContainer->link_list = list->next;
            }else{
                if(list->next == NULL){
                    tmp->next = NULL;
                }else{
                    tmp->next = list->next;
                }
            }
            releaseListElement(&list);
            break;
        }
        tmp = list;
        list = list->next;
        currentElement++;
    }
}

//appendlist
void appendlist(link_list* destContainer, link_list* srcContainer){
    list_struct* list = destContainer->link_list;
    if(destContainer->list_type != srcContainer->list_type){
        return;
    }
    while (list->next != NULL) {
        list = list->next;
    }
    list->next = srcContainer->link_list;
    destContainer->list_type += srcContainer->list_element_count;
    
}

//traverse a list
void traverseList(link_list* listContainer, elementAtIndex element){
    list_struct* list = listContainer->link_list;
    long currentElement = 1;
    while (list != NULL) {
        element(currentElement, list->data);
        list = list->next;
        currentElement++;
    }
}
/*************************
 *Private Methods
 ************************/
list_struct* newListElement(link_list_type type,void* data){
    list_struct *list_element = (list_struct*) calloc(sizeof(list_struct), 1);
    switch (type) {
        case link_list_int:{
            int* newData = (int*)calloc(sizeof(int), 1);
            *newData =*((int*)data);
            list_element->data = newData;
            break;
        }
        case link_list_double:{
            double* newData = (double*)calloc(sizeof(double), 1);
            *newData =*((double*)data);
            list_element->data = newData;
            break;
        }
        case link_list_float:{
            float* newData = (float*)calloc(sizeof(float), 1);
            *newData =*((float*)data);
            list_element->data = newData;
            break;
        }
        case link_list_string:{
            char* newData = (char*)calloc(sizeof(char), strlen((char*)data));
            strcpy(newData, (char*)data);
            list_element->data = newData;
            break;
        }
        case link_list_void:{
            list_element->data = data;
            break;
        }
    }
    list_element->next = NULL;
    return list_element;
}

void setValueFromlist(list_struct* list, link_list_type type, void* value){
    switch (type) {
        case link_list_int:{
            *((int*)(value)) = *(int*)list->data;
            break;
        }
        case link_list_double:{
            *((double*)(value)) = *(double*)list->data;
            break;
        }
        case link_list_float:{
           *((float*)(value)) = *(float*)list->data;
            break;
        }
        case link_list_string:{
            *((char**)value) =  (char*)list->data;
            break;
        }
        case link_list_void:{
            break;
        }
    }
}

short isListElementEqualToValue(list_struct* list, link_list_type type, void* value){
    short isEqual = 0;
    switch (type) {
        case link_list_int:{
            if(*((int*)(value)) == *(int*)list->data){
                isEqual = 1;
            }
            break;
        }
        case link_list_double:{
            if(*((double*)(value)) == *(double*)list->data){
                isEqual = 1;
            }
            break;
        }
        case link_list_float:{
            if(*((float*)(value)) == *(float*)list->data){
                isEqual = 1;
            }
            break;
        }
        case link_list_string:{
            isEqual = strcmp(((char*)(value)), (char*)list->data) == 0 ? 1 : 0;
            break;
        }
        case link_list_void:{
            break;
        }
    }
    return isEqual;
}

void releaseListElement(list_struct** ptrToElement){
    list_struct* element = *ptrToElement;
    free(element->data);
    free(element);
    *ptrToElement = NULL;
    
}