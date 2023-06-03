/* this file is the producer file */
#include "producer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


/******************
* Function Name: produce
* Input: void*
* Output:  struct Producer*
* Function Operation: creates the producers array
******************/
void* produce(void* arg){
    int counter = 0;
    Producer* p = (Producer*)arg;
    while(counter < p->productsNum){
       enqueue_bounded(p->bq,create_article(p,0));
       counter++;
    }
    enqueue_bounded(p->bq,create_article(p,1));
}

/******************
* Function Name: create_threads
* Input:int ,Producer**,pthread_t*
* Output:  ---
* Function Operation: creates the producers threads
******************/
void create_threads(int arrSize ,Producer** producers,pthread_t* threads){
    //create a thread to every producer
    for (int i = 0; i < arrSize; i++){
        // Create a new thread and pass the thread number as an argument
        if (pthread_create(&threads[i], NULL, produce, (void*)producers[i]) != 0 ){
            printf("Failed to create thread\n");
            exit(-1);
        }

   }

}
/******************
* Function Name: create_article
* Input: Producer* p,int end_flag
* Output:  Article*
* Function Operation: create the articles
******************/
Article* create_article(Producer* p,int end_flag){
    int category;
    Article* article = (Article*) malloc(sizeof (Article));
    if(!article){
        printf("Memory reallocation failed.\n");
        exit(-1);
    }
    article->producer_id = p->id;
    if(end_flag){
        article->end_flag = 1;
        return article;
    }
    article->end_flag = 0;
    //rand a category
    category = (rand() % 3) + 1;
    article->category = category;
    switch (category) {
        case 1:
            article->article_num = p->sportArticles;
            p->sportArticles++;
            break;
        case 2:
            article->article_num = p->newsArticles;
            p->newsArticles++;
            break;
        case 3:
            article->article_num = p->weatherArticles;
            p->weatherArticles++;
            break;
    }
    return article;
}

/******************
* Function Name: create_producer
* Input:int,int,int Producer[],int
* Output:  struct Producer*
* Function Operation: creates the producers array
******************/
  Producer** create_producer(int id,int productsNum, int qSize, Producer** producers,int arrSize ) {
    if(arrSize > 1){
        producers = ( Producer**)realloc(producers, (arrSize + 1) * sizeof(Producer*));
        // Check if memory reallocation was successful
        if (producers == NULL) {
            printf("Memory reallocation failed.\n");
            delete_allocation(arrSize,producers);
            return NULL;
        }
    }
    Producer* p;
    //in each index creates pointer to producer on the heap
    p = (Producer*)malloc(sizeof(Producer));
    BQ* q = init_bounded(qSize);
    // Check if memory allocation was successful
    if (!p || !q) {
        printf("Memory reallocation failed.\n");
        delete_allocation(arrSize,producers);
        return NULL;
    }
    producers[arrSize-1] = p;

    //initial the producer
    producers[arrSize-1]->id = id;
    producers[arrSize-1]->productsNum = productsNum;
    producers[arrSize-1]->newsArticles = 0;
    producers[arrSize-1]->sportArticles = 0;
    producers[arrSize-1]->weatherArticles = 0;
    producers[arrSize-1]->bq = q;
    return producers;
}

/******************
* Function Name: delete_allocation
* Input: int ,Producer**
* Output:  ---
* Function Operation: frees every index in the array
******************/
void delete_allocation(int arrSize,Producer** producer){
    for(int i=0;i<arrSize;i++){
        free(producer[i]->bq);
        free(producer[i]);
    }
    free(producer);
}