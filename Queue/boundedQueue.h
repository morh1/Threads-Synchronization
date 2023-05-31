//
// Created by mor on 5/27/23.
//

#ifndef EX3_BOUNDEDQUEUE_H
#define EX3_BOUNDEDQUEUE_H
#include "../Article/Article.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

//Define the producer's struct
typedef struct Node {
    Article* article;
    struct Node* next;
} Node;
typedef struct BQ {
    Node* head;
    Node* tail;
    int capacity;
    int count;
    pthread_mutex_t mutex;
    sem_t full;
    sem_t empty;

} BQ;

// Function declarations
BQ* init_bounded(int capacity);
Node* createNode(Article* article);
void enqueue_bounded(BQ* queue, Article* item);
Article * dequeue_bounded(BQ* queue);

#endif //EX3_BOUNDEDQUEUE_H
