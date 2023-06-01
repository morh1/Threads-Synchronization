//
// Created by mor on 5/27/23.
//

#ifndef EX3_UNBOUNDEDQ_H
#define EX3_UNBOUNDEDQ_H
#include "../Article/Article.h"
#include "../Queue/boundedQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
//Define the producer's struct
typedef struct UQ {
    Node* head;
    Node* tail;
    pthread_mutex_t mutex;
    sem_t full;
} UQ;

// Function declarations
UQ* init_unbounded();
void enqueue_unbounded(UQ* queue, Article* item);
Article * dequeue_unbounded(UQ* queue);
#endif //EX3_UNBOUNDEDQ_H
