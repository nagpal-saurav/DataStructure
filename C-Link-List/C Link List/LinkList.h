//
//  LinkList.h
//  C Link List
//
//  Created by Saurav Nagpal on 12/24/13.
//  Copyright (c) 2013 $aur@v Nagp@l.
//

#ifndef C_Link_List_LinkList_h
#define C_Link_List_LinkList_h

typedef enum link_list_type_enum{
    link_list_int,
    link_list_float,
    link_list_double,
    link_list_string,
    link_list_void // if specify then memory handling at developer end
}link_list_type;

typedef struct link_list_struct_info link_list;
/*-------------------------------------------- elementAtIndex -----
 |  Function elementAtIndex
 |
 |  Purpose:  callback syntax for traverse a list.
 |
 |  Parameters:
 |  link_list (IN)   -- link list to traverse.
 |	void*            -- pointer to data hold by the element at index
 |
 |  Returns:  None.
 *-------------------------------------------------------------------*/
typedef void (*elementAtIndex) (long index, void* data);

/*-------------------------------------------- newLinkList -----
 |  Function newLinkList
 |
 |  Purpose:  Create and return the new link list refrence.
 |
 |  Parameters:
 |	link_list_type (IN)   -- type of link list
 |
 |  Returns:  refrence of the newly created link list
 *-------------------------------------------------------------------*/
link_list* newLinkList(link_list_type type);
/*-------------------------------------------- releaseLinkList -----
 |  Function releaseLinkList
 |
 |  Purpose:  Release the memory used by link list.
 |
 |  Parameters:
 |	link_list (IN)   -- pointer to the link list to be freed.
 |
 |  Returns:  None
 *-------------------------------------------------------------------*/
void releaseLinkList(link_list** list);
/*-------------------------------------------- getElementCount -----
 |  Function getElementCount
 |
 |  Purpose:  Return the length of link list.
 |
 |  Parameters:
 |	link_list (IN)   -- link list.
 |
 |  Returns:  number of elements in link list.
 *-------------------------------------------------------------------*/
long getElementCount(link_list* list);
/*-------------------------------------------- getElementAtIndex -----
 |  Function getElementAtIndex
 |
 |  Purpose:  Return the element value at given index.
 |
 |  Parameters:
 |	link_list (IN)   -- link list.
 |  index     (IN)   -- index of element(start from 1).
 |  value     (OUT)  -- Pass the value back to calling method.
 |
 |  Returns:  None.
 *-------------------------------------------------------------------*/
void getElementAtIndex(link_list* list, long index, void* value);
/*-------------------------------------------- addElementInLinkList -----
 |  Function addElementInLinkList
 |
 |  Purpose:  Add the new element in a given list.
 |
 |  Parameters:
 |	link_list (IN)   -- link list.
 |  value     (IN)   -- Value to be added in a list.
 |
 |  Returns:  None.
 *-------------------------------------------------------------------*/
void addElementInLinkList(link_list* list, void* data);
/*-------------------------------------------- deleteElementInLinkList -----
 |  Function deleteElementInLinkList
 |
 |  Purpose:  delete the element from a given list.
 |
 |  Parameters:
 |	link_list (IN)   -- link list.
 |  value     (IN)   -- Value to be deleted from the list.
 |
 |  Returns:  None.
 *-------------------------------------------------------------------*/
void deleteElementInLinkList(link_list* list, void* data);
/*-------------------------------------------- deleteElementAtIndexInLinkList -----
 |  Function deleteElementAtIndexInLinkList
 |
 |  Purpose:  delete the element from a given list at given index.
 |
 |  Parameters:
 |	link_list (IN)   -- link list.
 |  index     (IN)   -- Index of the element to be deleted.
 |
 |  Returns:  None.
 *-------------------------------------------------------------------*/
void deleteElementAtIndexInLinkList(link_list* list, long index);
/*-------------------------------------------- appendlist -----
 |  Function appendlist
 |
 |  Purpose:  append the source list into destination.
 |
 |  Parameters:
 |	link_list (IN/OUT)      -- destination.
 |  link_list (IN)          -- source.
 |
 |  Returns:  None.
 *-------------------------------------------------------------------*/
void appendlist(link_list* dest, link_list* src);
/*-------------------------------------------- traverseList -----
 |  Function traverseList
 |
 |  Purpose:  provide a method to traverse all the elemnt of list sequentially.
 |
 |  Parameters:
 |  link_list (IN)                  -- link list to traverse.
 |	elementAtIndex (Callback)       -- element callback will be call.
 |
 |  Returns:  None.
 *-------------------------------------------------------------------*/
void traverseList(link_list* list, elementAtIndex element);


#endif
