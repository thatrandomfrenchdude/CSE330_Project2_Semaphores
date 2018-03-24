//
//  TCB.h
//  proj-2
//
//  Created by Nicholas Debeurre on 10/16/17.
//  Copyright © 2017 Debeurre. All rights reserved.
//

#ifndef tcb_h
#define tcb_h

#include <ucontext.h>
#include <string.h>

typedef struct TCB_t {
    struct TCB_t     *next;
    struct TCB_t     *prev;
    ucontext_t      context;
} TCB_t;



void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size)
{
    memset(tcb, '\0', sizeof(TCB_t));
    getcontext(&tcb->context);
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    makecontext(&tcb->context, function, 0);
}


#endif /* tcb_h */

