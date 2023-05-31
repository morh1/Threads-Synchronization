#include "boundedQueue.h"


/******************
* Function Name: init
* Input: ---
* Output:  BQ,int
* Function Operation: crete init bounded queue on the heap
******************/
BQ* init_bounded(int capacity){
    BQ* queue = (BQ*) malloc(sizeof(BQ));
    if (queue == NULL) {
        printf("Memory reallocation failed.\n");
        return NULL;
    }
    queue->capacity = capacity;
    queue->head = NULL;
    queue->tail = NULL;
    queue->count = 0;

    //init the full semaphore
    if(sem_init(&queue->full, 0,0) != 0){
        perror("Error initialize 'full'");
        free(queue);
        exit(1);
    }
    //init the empty semaphore
    if(sem_init(&queue->empty, 0,queue->capacity) != 0){
        perror("Error initialize 'empty'");
        sem_destroy(&queue->full);
        free(queue);
        exit(1);
    }
    //init the mutex
    if(pthread_mutex_init(&queue->mutex, NULL) != 0){
        perror("Error initialize 'mutex'");
        sem_destroy(&queue->full);
        sem_destroy(&queue->empty);
        free(queue);
        exit(1);
    }
    return queue;

}

/******************
* Function Name: createNode
* Input: Article
* Output:  Node*
* Function Operation: creates new node that contain the data in the input
******************/
// Function to create a new node
Node* createNode(Article* article) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory reallocation failed.\n");
        return NULL;
    }
    newNode->article = article;
    newNode->next = NULL;
    return newNode;
}

/******************
* Function Name: enqueue
* Input: BQ* queue, Node* item
* Output:  ---
* Function Operation: insert new Node to the end of the bounded queue
******************/
void enqueue_bounded(BQ* queue, Article* article) {

    Node* item = createNode(article);

    sem_wait(&queue->empty);
    //lock the mutex (prevent insertion and takeout at the same time)
    pthread_mutex_lock(&queue->mutex);

    if(!queue->head){
        queue->head = item;
        queue->tail = item;

    }
    else{
        Node* temp = queue->tail;
        queue->tail = item;
        temp->next = item;

    }
    queue->count++;

    pthread_mutex_unlock(&queue->mutex);
    sem_post(&queue->full);
    //printf(" insert, producer id: %d article type:%d\n",article->producer_id,queue->head->article->category);
}

/******************
* Function Name: dequeue
* Input: BQ* queue
* Output:  Node*
* Function Operation: remove and return the first Node's Article from the head of the queue (fifo)
******************/
Article * dequeue_bounded(BQ* queue) {

    sem_wait(&queue->full);
    //lock the mutex (prevent insertion and takeout at the same time)
    pthread_mutex_lock(&queue->mutex);

    Article* tempArticle = queue->head->article;
    //printf("removing, producer id: %d article type:%d\n",queue->head->article->producer_id,queue->head->article->category);
    Node* tempNode = queue->head;
    //update the queue (critical code)
    queue->head = queue->head->next;
    free(tempNode);
    queue->count--;

    pthread_mutex_unlock(&queue->mutex);
    sem_post(&queue->empty);

    return tempArticle;
}