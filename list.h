//
// Created by danip on 22/09/2022.
//
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#ifndef P0_LIST_H
#define P0_LIST_H
#define LNULL NULL

#endif //P0_LIST_H

typedef struct tNode* tPosL;

typedef struct tNode{
    char* datos;
    tPosL next;
}tNode;

typedef tPosL tList;

void createList(tList* L);
bool createNode(tPosL* p);
char* getChar(tPosL p,tList L);
void printList(tList L);
bool insertItem(char d,tList L);
void printn(char* param[],tList L);
void deleteAtPosition (tPosL p, tList L);
