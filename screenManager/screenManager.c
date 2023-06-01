//
// Created by mor on 6/1/23.
//
#include "screenManager.h"
/******************
* Function Name: init_screen_manager
* Input: BQ* bounded_queue
* Output: ScreenManager*
* Function Operation: init new screen manager
******************/
ScreenManager* init_screen_manager(BQ* bounded_queue){
    ScreenManager* screen_manager = (ScreenManager*)malloc(sizeof(ScreenManager));
    if (screen_manager == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    screen_manager->boundedQ = bounded_queue;
    return screen_manager;
}
/******************
* Function Name: print
* Input: void* arg
* Output: void*
* Function Operation: the function prints to screen
******************/
void* print(void* arg){
    ScreenManager* screen_manager = (ScreenManager*)arg;
    int counter = 0;
    Article* article;
    while(1){
        article = dequeue_bounded(screen_manager->boundedQ);
        if(article->end_flag == 0){
            counter++;
            if(counter == COEDITORS_NUM){
                break;
            }
        }
        switch (article->category) {
            case 1:
                print("Producer %d SPORTS %d",article->producer_id,article->article_num);
                break;
            case 2:
                print("Producer %d NEWS %d",article->producer_id,article->article_num);
                break;
            case 3:
                print("Producer %d WEATHER %d",article->producer_id,article->article_num);
                break;
            default:
                break;
        }
    }

}
/******************
* Function Name: create_dispatcher_thread
* Input: Dispatcher*
* Output: ---
* Function Operation: the function creates the dispatcher's threads
******************/
void create_screen_manager_thread(ScreenManager* screen_manager,pthread_t* threads,int threadsCount){

    if (pthread_create(&threads[threadsCount], NULL, print, (void*)screen_manager) != 0 ){
        printf("Failed to create thread\n");
        exit(-1);
    }

}