//
// Created by mor on 5/26/23.
//

#ifndef EX3_PRODUCER_H
#define EX3_PRODUCER_H
#include "../Queue/boundedQueue.h"
//Define the producer's struct
typedef struct Producer {
    int id;
    int productsNum;
    int sportArticles;
    int weatherArticles;
    int newsArticles;
    BQ* bq;

} Producer;

// Function declarations
Producer** create_producer(int v1,int v2, int v3, Producer** p, int arrSize);
void create_threads( int arrSize,Producer** p);
void* produce(void* arg);
void delete_allocation(int arrSize,Producer** producer);
Article* create_article(Producer* p,int end_flag);

#endif //EX3_PRODUCER_H