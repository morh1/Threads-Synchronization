//
// Created by mor on 5/27/23.
//
#include "dispatcher.h"


/******************
* Function Name: init
* Input: Producer** p
* Output: ---
* Function Operation: init new Dispatcher
******************/
Dispatcher*


init_dispatcher(BQ** bqs,int arrSize){
    Dispatcher* d = (Dispatcher*)malloc(sizeof(Dispatcher));
    if (d == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    d->bqs = bqs;
    d->BQnum = arrSize;

    return d;
}

/******************
* Function Name: init
* Input: Producer** p
* Output: ---
* Function Operation: init new Dispatcher
******************/
void sort(Article* article,Dispatcher* d){
    if(article->end_flag != 0){
        switch (article->category) {
            case 1:
                enqueue_unbounded(d->uqs[0],article);
                break;
            case 2:
                enqueue_unbounded(d->uqs[1],article);
                break;
            case 3:
                enqueue_unbounded(d->uqs[2],article);
                break;
        }
    }
    else {
        //update all qoueue that there is no more articles
        enqueue_unbounded(d->uqs[0],article);
        enqueue_unbounded(d->uqs[1],article);
        enqueue_unbounded(d->uqs[2],article);
    }

}
void create_dispatcher_thread(Dispatcher* d){
    pthread_t thread;
    if (pthread_create(&thread, NULL, consume, (void*)d) != 0 ){
        printf("Failed to create thread\n");
        exit(-1);
    }
    // Wait for the thread to finish
    if (pthread_join(thread, NULL) != 0) {
        printf("Failed to join thread\n");
        exit(-1);
    }
}
/******************
* Function Name: consume
* Input: void*
* Output: ---
* Function Operation: the function consume the articles frome the bounded queues in round robin alg
******************/
void* consume(void* arg){
    Dispatcher* d = (Dispatcher*)arg;
    Article* article;
    int completed = 0;
    int position = 0;
    Article* empty_article;

    while(completed != d->BQnum)
    {

        while(d->bqs[position] == NULL){
            position = (position+1)%(d->BQnum);
        }
        article = dequeue_bounded(d->bqs[position]);
        // the producer aim to the capacity
        if(article->end_flag == 1){
            empty_article = article;
            d->bqs[position] = NULL;
            completed++;
        }
        else{
           sort(article,d);
        }
        position = (position+1)%(d->BQnum);
    }
    sort(empty_article,d);
}
