#include <stdio.h>
#include <stdlib.h>
#include "Producer/producer.h"
#include "Queue/boundedQueue.h"
#include "Dispatcher/dispatcher.h"


/******************
* Function Name: create_producers_arr
* Input:char* path, int* counter
* Output: Producer **
* Function Operation: create arr of producers
******************/
Producer ** create_producers_arr(char* path,int* counter){
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
    int val1,val2,val3;
    // Read and print the numbers from the file
    while (fscanf(file, "%d%d%d", &val1,&val2,&val3) == 3) {
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
        if(bqArr == NULL){
            printf("Memory allocation failed.\n");
            exit(1);
        }
        bqArr[i] = p[i]->bq;
    }
    return bqArr;
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
    //create arr of producers
    Producer** p = create_producers_arr(path,ptrCounter);
    //create arr of BQ
    BQ** bq = create_boundedQ_arr(p,producersCounter);
    create_threads(producersCounter,p);
    Dispatcher* dispatcher = init_dispatcher(bq,producersCounter);
    create_dispatcher_thread(dispatcher);

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