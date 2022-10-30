
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "headed_linked_list.h"
#define LNULL NULL

void deleteAtPosition(tPosL p, tList  *L) ;

struct malloc_t{
    void *address;
    int tamano;
    struct tm* time;
};

struct mmap_t {
    int tamano;
    void *address;
    struct tm* time;
    char name[256];
    int id;
};

struct shared_t{
    void *address;
    int tamano;
    struct tm* time;
    int key;
};
