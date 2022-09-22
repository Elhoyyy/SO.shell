//
// Created by eloys on 21/09/2022.
//

#ifndef SO_SHELL_HEADED_LINKED_LIST_H
#define SO_SHELL_HEADED_LINKED_LIST_H

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H
#define LNULL NULL

#include <stdbool.h>
#include "types.h"

typedef struct tNode* tPosL;
typedef struct tNode{
    char* datos;
    tPosL next;
}tNode;

typedef tPosL tList;

void createEmptyList(tList* L);
bool isEmptyList(tList L);
tPosL first(tList L);
tPosL last(tList L);
tPosL next(tPosL p, tList L);

tPosL previous ( tPosL p, tList L);

bool insertItem(char* d, tPosL p, tList *L);

void deleteAtPosition (tPosL p, tList *L);

char getItem( tPosL p, tList L);
tPosL findItem (char* d, tList L);




#endif //SO_SHELL_HEADED_LINKED_LIST_H


