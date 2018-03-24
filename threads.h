//
//  threads.h
//  cse330_P2
//
//  Created by Nicholas Debeurre on 9/19/17.
//  Copyright © 2017 Debeurre. All rights reserved.
//

#include <stdlib.h>
#include "q.h"

TCB_t *RunQ = NULL;

void start_thread(void (*function) (void));

#ifndef threads_h
#define threads_h

void start_thread(void (*function) (void))
{
    void *stack = malloc(8192);
    TCB_t *qItem = NewItem();
    init_TCB(qItem, function, stack, 8192);
    AddQueue(&RunQ, qItem);
}

void run()
{
    ucontext_t parent;
    getcontext(&parent);
    swapcontext(&parent, &(RunQ->context));
}

void yield()
{
    TCB_t *currContext = RunQ;
    RotateQ(&RunQ);
    swapcontext(&(currContext -> context), &(RunQ -> context));
}

#endif /* threads_h */

