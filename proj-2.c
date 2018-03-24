//
//  main.c
//  proj-2
//
//  Created by Nicholas Debeurre on 10/16/17.
//  Copyright © 2017 Debeurre. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include "sem.h"
#define bSize 10

//global variable
int globular = 0;

//method 1 variable
Sem* s;

//method 2 variables
int buffer[bSize];
int in = 0;
int out = 0;
Sem* s1; //mutex 1
Sem* s2; //mutex 2
Sem* empty;
Sem* full;

void printBuf()
{
    int i;
    for (i =0; i < bSize; i++)
    {
        if (i == bSize - 1)
            printf("%d\n", buffer[i]);
        else
            printf("%d ", buffer[i]);
    }
}

////method 1 functions
//void addOne()
//{
//    int x = 0;
//    while (1)
//    {
//        P(s);
//        printf("X value = %d\n", x);
//        printf("Global value: %d\n", globular);
//        globular++;
//        x++;
//        sleep(1);
//        V(s);
//    }
//}
//
//void addTwo()
//{
//    int y = 0;
//    while (1)
//    {
//        P(s);
//        printf("Y value = %d\n", y);
//        printf("Global value: %d\n", globular);
//        globular++;
//        y+=2;
//        sleep(1);
//        V(s);
//    }
//}

//method 2 functions
void producer1()
{
    while (1)
    {
        P(s1); //mutex 1
        P(empty);
        buffer[in] = 1;
        in = (in + 1) % bSize;
        printf("Producer 1: ");
        printBuf();
        sleep(1);
        V(full);
        V(s1); //mutex 1
    }
}

void producer2()
{
    while (1)
    {
        P(s1); //mutex 2
        P(empty);
        buffer[in] = 1;
        in = (in + 1) % bSize;
        printf("Producer 2: ");
        printBuf();
        sleep(1);
        V(full);
        V(s1); //mutex 2
    }
}

void consumer1()
{
    while (1)
    {
        P(s2); //mutex 1
        P(full);
        buffer[out] = 0;
        out = (out + 1) % bSize;
        printf("Consumer 1: ");
        printBuf();
        sleep(1);
        V(empty);
        V(s2); //mutex 1
    }
}

void consumer2()
{
    while (1)
    {
        P(s2); //mutex 2
        P(full);
        buffer[out] = 0;
        out = (out + 1) % bSize;
        printf("Consumer 2: ");
        printBuf();
        sleep(1);
        V(empty);
        V(s2); //mutex 2
    }
}

////method 1 main
//int main()
//{
//    InitQueue(&RunQ);
//    s = (Sem*)malloc(sizeof(Sem)); //allocate for s
//    InitSem(s, 1); //initialize s1
//    start_thread(addOne);
//    start_thread(addTwo);
//    run();
//}

//method 2 main
int main()
{
    //initialize all the things
    InitQueue(&RunQ); //initialize RunQ
    s1 = (Sem*)malloc(sizeof(Sem)); //malloc for s1
    s2 = (Sem*)malloc(sizeof(Sem)); //malloc for s2
    empty = (Sem*)malloc(sizeof(Sem)); //malloc for empty
    full = (Sem*)malloc(sizeof(Sem)); //malloc for full
    InitSem(empty, bSize); //init empty
    InitSem(full, 0); //init full
    InitSem(s1, 1); //init s1
    InitSem(s2, 1); //init s2
    memset(buffer, 0, bSize); //set all values in buffer to 0
    
    //start all the threads
    start_thread(producer1);
    start_thread(producer2);
    start_thread(consumer1);
    start_thread(consumer2);
    run();
}
