#include <stdio.h>
#include <stdlib.h>
#include "Producer/producer.h"
#include "Queue/boundedQueue.h"
#include "Dispatcher/dispatcher.h"
#include "CoEditor/coEditor.h"
#include "screenManager/screenManager.h"
#define CATEGORIES_NUM 3

/******************
* Function Name: create_producers_arr
* Input:char* path, int* counter
* Output: Producer **
* Function Operation: create arr of producers
******************/
Producer ** create_producers_arr(char* path,int* counter,int* managerQSize){
    // Open the file in read mode
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        exit(1);
    }

    // Allocate initial memory using malloc() for the producers array.
    Producer** producers = ( Producer **)malloc(sizeof(Producer*));
    Producer** temp;
    // Check if memory allocation was successful
    if (producers == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    int val1,val2,val3,result;
    // Read and print the numbers from the file
    while ( fscanf(file, "%d%d%d", &val1,&val2,&val3) == 3) {
        (*counter)++;
        temp = create_producer(val1,val2,val3,producers,*counter);
        if(temp){ producers = temp; }
        else{
            free(temp);
            free(producers);
            fclose(file);
            exit(1);
        }
    }

    *managerQSize = val1;
    // Close the file
    fclose(file);
    return producers;
}

/******************
* Function Name: create_boundedQ_arr
* Input:Producer** , int
* Output: int
* Function Operation: create arr of bounded queues
******************/
BQ** create_boundedQ_arr(Producer** p, int arrSize){
    BQ** bqArr = (BQ**)malloc(arrSize * sizeof(BQ*));
    if(bqArr == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for(int i=0;i<arrSize;i++){
        bqArr[i] =  (BQ*)malloc( sizeof(BQ));
        if(bqArr[i] == NULL){
            printf("Memory allocation failed.\n");
            exit(1);
        }
        bqArr[i] = p[i]->bq;
    }
    return bqArr;
}
/******************
* Function Name: create_co_editor_arr
* Input: UQ** uq,BQ* manager_boundedQ
* Output: CoEditor**
* Function Operation: create arr of the co-editors
******************/
CoEditor** create_co_editor_arr(UQ** uq,BQ* manager_boundedQ){
    CoEditor** co_editors = (CoEditor**)malloc( CATEGORIES_NUM * sizeof(CoEditor*));
    if(co_editors == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for(int i=0; i< CATEGORIES_NUM; i++){

        co_editors[i] = init_coEditor(manager_boundedQ,uq[i]);
    }
    return co_editors;
}

/******************
* Function Name: create_unboundedQ_arr
* Input:Producer** , int
* Output: int
* Function Operation: create arr of bounded queues
******************/
UQ** create_unboundedQ_arr(){
    BQ** unbounded = (UQ**)malloc( CATEGORIES_NUM * sizeof(UQ*));
    if(unbounded == NULL){
        printf("Memory allocation failed.\n");
        exit(1);
    }
    for(int i=0; i< CATEGORIES_NUM; i++){
        unbounded[i] =  init_unbounded();

    }
    return unbounded;
}

/******************
* Function Name: create_producers_arr
* Input:char* path, int* counter
* Output: Producer **
* Function Operation: responsible for the project's flow
******************/
int flow_control(char* path){
    int producersCounter = 0;
    int* ptrCounter = &producersCounter;
    int managerQSize;
    //create arr of producers
    Producer** p = create_producers_arr(path,ptrCounter,&managerQSize);
    int threadsNum = producersCounter+5;
    pthread_t threads[threadsNum];
    //create arr of bounded queue
    BQ** bq = create_boundedQ_arr(p,producersCounter);
    //create arr of unbounded queue
    UQ** uq = create_unboundedQ_arr();
    create_threads(producersCounter,p,&threads);
    Dispatcher* dispatcher = init_dispatcher(bq,uq,producersCounter,CATEGORIES_NUM);
    create_dispatcher_thread(dispatcher,&threads);
    BQ* manager_boundedQ = init_bounded(managerQSize);
    CoEditor** coEditors = create_co_editor_arr(uq,manager_boundedQ);

    create_co_editor_thread( coEditors, CATEGORIES_NUM,&threads,producersCounter);
    ScreenManager* screen_manager = init_screen_manager(manager_boundedQ);
    create_screen_manager_thread(screen_manager,threads,threadsNum-1);

    for(int i=0; i<threadsNum;i++){
        //Wait for the thread to finish
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Failed to join thread\n");
            exit(-1);}
    }

    //delete_allocation(*producersCounter,p);

    return 0;
}

int main(int argc, char* argv[]) {
     //Ensure at least one command-line argument (the file path) is provided
    if (argc < 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }
    flow_control(argv[1]);
}