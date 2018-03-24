//
//  q.h
//  proj-2
//
//  Created by Nicholas Debeurre on 10/16/17.
//  Copyright © 2017 Debeurre. All rights reserved.
//

#include <stdlib.h>
#include "TCB.h"

#ifndef q_h
#define q_h

TCB_t *NewItem()
{
    TCB_t *newNode = (TCB_t*)malloc(sizeof(TCB_t));
    newNode -> next = NULL;
    newNode -> prev = NULL;
    return newNode;
}

//initializes an empty Queue where the head and tail are the same
void InitQueue(TCB_t **newQ)
{
    *newQ = NULL;
}

void AddQueue(TCB_t **currQ, TCB_t *itemToAdd)
{
    if (*currQ == NULL)
    {
        *currQ = itemToAdd;
        itemToAdd -> next = *currQ;
        itemToAdd -> prev = *currQ;
    }
    else
    {
        itemToAdd -> next = *currQ;
        itemToAdd -> prev = (*currQ) -> prev;
        (*currQ) -> prev = itemToAdd;
        itemToAdd -> prev -> next = itemToAdd; //here
    }
}

TCB_t *DelQueue(TCB_t **currQ)
{
    TCB_t *temp = *currQ;
    if ((*currQ) == NULL)
        return NULL;
    else
    {
        (*currQ) -> prev -> next = (*currQ) -> next;
        (*currQ) -> next -> prev = (*currQ) -> prev;
        *currQ = (*currQ) -> next;
        if ((*currQ) == (*currQ) -> next)
            *currQ = NULL;
        temp -> next = NULL;
        temp -> prev = NULL;
        return temp;
    }
}

void RotateQ(TCB_t **headPtr)
{
    *headPtr = (*headPtr) -> next;
}

//void printQ(TCB_t **Q)
//{
//    TCB_t *temp = *Q;
//    if (temp != NULL)
//    {
//        while (temp -> next != *Q)
//        {
//            printf("%d ", temp -> context);
//            temp = temp -> next;
//        }
//        printf("%d\n", temp -> context);
//    }
//    else
//        printf("Queue is empty");
//}

#endif /* q_h */

