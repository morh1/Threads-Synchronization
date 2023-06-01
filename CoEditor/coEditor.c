//
// Created by mor on 6/1/23.
//

#include "coEditor.h"

/******************
* Function Name: init_coEditor
* Input: BQ* boundedQ,UQ* unboundedQ
* Output: CoEditor*
* Function Operation: init the co-Editor
******************/
CoEditor* init_coEditor(BQ* boundedQ,UQ* unboundedQ){
    CoEditor* coEditor= (CoEditor*)malloc(sizeof(CoEditor));
    if (coEditor == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    coEditor->bounded_queue = boundedQ;
    coEditor->unbounded_queue = unboundedQ;

    return coEditor;
}
/******************
* Function Name: create_dispatcher_thread
* Input: CoEditor** coEditors,int arrSize
* Output: ---
* Function Operation: the function creates the co-editor's threads
******************/
void create_co_editor_thread(CoEditor** coEditors,int arrSize,pthread_t* threads,int treadsCount){

    for (int i = 0; i < arrSize; i++){
         //Create a new thread and pass the thread number as an argument
        if (pthread_create(&threads[treadsCount + i + 1], NULL, edit, (void*)coEditors[i]) != 0 ){
            printf("Failed to create thread\n");
            exit(-1);
        }
    }

}

/******************
* Function Name: edit
* Input: Article* article,Dispatcher* d
* Output: ---
* Function Operation: sort the articles by their category
******************/
void* edit(void* arg){
    int counter=0;
    CoEditor* editor = (CoEditor*)arg;
    Article* article;
    while(1){
        counter++;
        article = dequeue_unbounded(editor->unbounded_queue);
        if(article->end_flag == 1){
            break;
        }
        usleep(100000);
        enqueue_bounded(editor->bounded_queue,article);

    }
    enqueue_bounded(editor->bounded_queue,article);
}