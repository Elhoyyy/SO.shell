//
// Created by elhoyyy on 25/11/22.
//

#ifndef PRUEBA_HEADED_LINKED_JOBLIST_H
#define PRUEBA_HEADED_LINKED_JOBLIST_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define TAMANO 2048

#define ACTIVE 3
#define SIGNALED 2
#define STOPPED 1
#define FINISHED 0

typedef struct JobNode* posJ;


struct JobNode{
    int pid;
    uid_t  uid;
    char * status;
    int priority;
    int returnstatus;
    time_t time;
    posJ next;
    char lineacomando[TAMANO];
};

typedef posJ JobList;


void createJobList(JobList * L);
bool insertJobList(JobList L, int pid, char* status, int priority , char lineacomnando[TAMANO], time_t tiempo, uid_t  uid);
void deleteAtJPosition (posJ p, JobList L);



#endif //PRUEBA_HEADED_LINKED_JOBLIST_H
