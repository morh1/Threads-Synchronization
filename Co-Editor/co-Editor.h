//
// Created by mor on 5/31/23.
//

#ifndef EX3_CO_EDITOR_H
#define EX3_CO_EDITOR_H
#include "../Queue/unboundedQ.h"
#include "../Producer/producer.h"
#include "../Article/Article.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Define the producer's struct
typedef struct Dispatcher {
    BQ** bqs = BQ*[3];
    UQ*[3] uqs
    int BQnum;

} Dispatcher;

#endif //EX3_CO_EDITOR_H
