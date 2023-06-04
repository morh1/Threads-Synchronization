//
// Created by mor on 6/1/23.
//

#ifndef EX3_SCREENMANAGER_H
#define EX3_SCREENMANAGER_H
#define COEDITORS_NUM 3
#include "../Queue/boundedQueue.h"
#include "../Article/Article.h"
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
//Define the producer's struct
typedef struct ScreenManager{
   BQ* boundedQ;
} ScreenManager;
ScreenManager* init_screen_manager(BQ* bounded_queue);
void create_screen_manager_thread(ScreenManager* screen_manager,pthread_t* threads,int threadsCount);
#endif //EX3_SCREENMANAGER_H

