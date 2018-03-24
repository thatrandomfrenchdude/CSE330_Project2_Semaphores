//
//  sem.h
//  proj-2
//
//  Created by Nicholas Debeurre on 10/16/17.
//  Copyright © 2017 Debeurre. All rights reserved.
//

#include <stdlib.h>
#include <stdbool.h>
#include "threads.h"

#ifndef sem_h
#define sem_h

typedef struct Sem
{
    int value;
    TCB_t* queue;
} Sem;

void InitSem(Sem* mySem, int val)
{
    mySem -> value = val;
}

void P(Sem* mySem)
{
    mySem -> value--;
    if (mySem -> value < 0)
    {
        TCB_t* temp = DelQueue(&RunQ);
        AddQueue(&(mySem -> queue), temp);
        swapcontext(&(temp -> context), &(RunQ -> context));
    }
            
}

void V(Sem* mySem)
{
    mySem -> value++;
    if (mySem -> value <= 0)
    {
        TCB_t* temp = DelQueue(&(mySem ->queue));
        AddQueue(&RunQ, temp);
    }
    yield();
}

#endif /* sem_h */
