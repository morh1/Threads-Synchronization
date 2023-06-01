//
// Created by mor on 6/1/23.
//

#ifndef EX3_COEDITOR_H
#define EX3_COEDITOR_H
#include "../Queue/unboundedQ.h"
#include "../Producer/producer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//Define the producer's struct
typedef struct CoEditor {
    BQ* bounded_queue;
    UQ* unbounded_queue;

}CoEditor;
void* edit(void* arg);
void create_co_editor_thread(CoEditor** coEditors,int arrSize,pthread_t* treads,int treadsCount);
CoEditor* init_coEditor(BQ* boundedQ,UQ* unboundedQ);

#endif //EX3_COEDITOR_H
