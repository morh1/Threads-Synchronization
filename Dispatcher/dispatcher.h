//
// Created by mor on 5/27/23.
//
#ifndef EX3_DISPATCHER_H
#define EX3_DISPATCHER_H
#include "../Queue/unboundedQ.h"
#include "../Producer/producer.h"
#include "../Article/Article.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Define the producer's struct
typedef struct Dispatcher {
    BQ** bqs;
    UQ** uqs;
    int BQnum;

} Dispatcher;
void insert(UQ* bq,Article* article);
Dispatcher* init_dispatcher(BQ** b,int arrSize);
void sort(Article* article,Dispatcher* d);
void* consume(void* arg);
void create_dispatcher_thread(Dispatcher* d);
#endif //EX3_DISPATCHER_H
