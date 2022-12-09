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
    uid_t  uid;
    char * status;
    int priority;
    int returnstatus;
    time_t time;
    posJ next;
    char lineacomando[1048];
};

typedef posJ JobList;


void createJobList(JobList * L);
bool insertJobList(JobList L, int pid, char* status, int priority , char *lineacomnando, time_t tiempo, uid_t  uid);
void deleteAtJPosition (posJ p, JobList L);



#endif //PRUEBA_HEADED_LINKED_JOBLIST_H
