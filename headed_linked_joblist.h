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

#define ACTIVE 3
#define SIGNALED 2
#define STOPPED 1
#define FINISHED 0

typedef struct JobNode* posJ;


struct JobNode{
    int pid;
    int status;
    int priority;
    char * lineacomando;
    time_t time;
    posJ next;
}JobNode;

typedef posJ JobList;


void createJobList(JobList * L);
bool insertJobList(JobList L, int pid, int status, int priority , char *lineacomnando, time_t tiempo);
void deleteAtJPosition (posJ p, JobList L);



#endif //PRUEBA_HEADED_LINKED_JOBLIST_H
