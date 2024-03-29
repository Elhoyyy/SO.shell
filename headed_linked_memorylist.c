//
// Created by dani on 30/10/22.
//
#include "headed_linked_memorylist.h"
#include <sys/stat.h>
#include <time.h>

void createMemoryList(MemoryList * L){
    pos cabeceira;
    cabeceira=malloc(sizeof(**L));
    *L=cabeceira;
    cabeceira->next=NULL;
}

bool createNodeMem( pos* p){
    *p= malloc(sizeof(**p));
    return *p!=LNULL;
}

bool insertMemory(MemoryList L, int tipo, char* dirrecion,time_t t,long tamano, int df, char* nombre,int key) {
    pos p, q; //LAS VARIABLES 'r' Y 'q' ACTUÁN COMO NODOS PARA APUNTAR AL NODO QUE QUEREMOS INTRODUCIR EN LA LISTA.

    if (!createNodeMem(&q)) //SI NO HAY NODO SE RETORNA FALSO.
        return false;

    q->address=dirrecion;
    q->size=tamano;
    q->tipo=tipo;
    q->time=t;
    q->next = LNULL;
    if(tipo==3){
        q->id=df;
        strcpy(q->fich,nombre);
    }else if(tipo==2)
        q->key=key;

    if (L->next == LNULL) { //LISTA VACÍA.
        L->next = q;
    } else{
        for(p=L->next;p->next!=NULL;p=p->next);
        p->next=q;
    }
    return true;
}
char *ptr2string( const void *ptr ) {
    //int size = snprintf( NULL, 0, "%p", ptr );
    static char result[1000];
    sprintf( result, "%p", ptr );
    return result;
}
pos EncontrarPosicion(MemoryList Lista, char* direccion) {
    pos p = Lista->next;

    while (p != NULL) {
        if (strcmp(ptr2string(p->address),direccion)==0)
            return p;
        p = p->next;
    }

    return NULL;

}
pos EncontrarFichero (MemoryList Lista, char* nombre){
    pos p = Lista->next;

    while (p != NULL) {
        if (p->tipo==MMAP && strcmp(p->fich,nombre)==0)
            return p;
        p = p->next;
    }

    return NULL;

}

pos EncontrarTamano(MemoryList Lista, long tamano) {
    pos p = Lista->next;

    while (p != NULL) {
        if (p->tipo==1 && p->size == tamano)
            return p;
        p = p->next;
    }

    return NULL;
}
void deleteAtPosition (pos p, MemoryList L) {
    pos q;
    if (p == L->next) { //ELIMINAR ELEMENTO DEL INICIO.
        L->next=p->next;
    } else if (p->next == LNULL) { //ELIMINAR ELEMENTO DEL FINAL.
        for (q = L; q->next != p; q = q->next);
        q->next = LNULL;

    } else { //ELIMINAR ELEMENTO DEL MEDIO.
        q = p->next;
        strcpy(p->fich,q->fich);
        p->address=q->address;
        p->size=q->size;
        p->tipo=q->tipo;
        p->time=q->time;
        p->id=q->id;
        p->next = q->next;
        p->key=q->key;
        p = q;
    }
    free(p);

}
char* getAdrres(pos p){
    return p->address;
}

pos EncontrarLlave(MemoryList Lista, int key) {
    pos p = Lista->next;

    while (p != NULL) {
        if (p->tipo==SHARED && p->key==key)
            return p;
        p = p->next;
    }

    return NULL;

}
void deleteMemorylist (MemoryList L){
    pos q, p ;
    q=L->next;
    while(q!=NULL){
        p=q;
        q=q->next;
        free (p);

    }
    L->next=NULL;
}



