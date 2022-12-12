//
// Created by dani on 30/10/22.
//
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define MALLOC 1
#define SHARED 2
#define MMAP 3
#define P0_LIST_H
#define LNULL NULL
#ifndef UNTITLED1_HEADED_LINKED_MEMORYLIST_H
#define UNTITLED1_HEADED_LINKED_MEMORYLIST_H
#include <time.h>

typedef struct MemoryNode* pos;

typedef struct MemoryNode{
    void *address;
    time_t time;
    char fich[256];
    int id;
    int tipo;
    long size;
    int key;
    pos next;

}MemoryNode;

typedef pos MemoryList;

void createMemoryList(MemoryList * L);
bool insertMemory(MemoryList L, int tipo, char* dirrecion,time_t t,long tamano, int df, char* nombre,int key);
pos EncontrarPosicion(MemoryList Lista, char* direccion);
pos EncontrarTamano(MemoryList Lista, long tamano);
pos EncontrarFichero(MemoryList Lista, char* nombre);
void deleteAtPosition (pos p, MemoryList L);
char* getAdrres(pos p);
char *ptr2string( const void *ptr );
pos EncontrarLlave(MemoryList Lista, int key);
void deleteMemorylist (MemoryList L);

#endif //UNTITLED1_HEADED_LINKED_MEMORYLIST_H
