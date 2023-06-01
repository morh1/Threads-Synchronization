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
Dispatcher* init_dispatcher(BQ** bqs,UQ ** uqs,int arrSize,int unbounded_size){
    Dispatcher* d = (Dispatcher*)malloc(sizeof(Dispatcher));
    if (d == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    d->bqs = bqs;
    d->BQnum = arrSize;
    for(int i=0;i<unbounded_size;i++){
        d->uqs[i] = uqs[i];
    }

    return d;
}

/******************
* Function Name: sort
* Input: Article* article,Dispatcher* d
* Output: ---
* Function Operation: sort the articles by their category
******************/
void sort(Article* article,Dispatcher* d){
    //printf("sort, producer id: %d article type:%d\n",article->producer_id,article->category);
    if(article->end_flag == 0){
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
            default:
                break;
        }
    }
    else {
        //update all queue that there is no more articles
        enqueue_unbounded(d->uqs[0],article);
        enqueue_unbounded(d->uqs[1],article);
        enqueue_unbounded(d->uqs[2],article);
    }

}

/******************
* Function Name: create_dispatcher_thread
* Input: Dispatcher*
* Output: ---
* Function Operation: the function creates the dispatcher's threads
******************/
void create_dispatcher_thread(Dispatcher* d,pthread_t* threads){

    if (pthread_create(&threads[d->BQnum], NULL, consume, (void*)d) != 0 ){
        printf("Failed to create thread\n");
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
