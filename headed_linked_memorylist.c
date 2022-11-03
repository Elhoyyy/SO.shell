

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

bool insertMemory(MemoryList L, int tipo, char* dirrecion,time_t t,long tamano, int df, char* nombre) {
    pos p, q; //LAS VARIABLES 'r' Y 'q' ACTUÁN COMO NODOS PARA APUNTAR AL NODO QUE QUEREMOS INTRODUCIR EN LA LISTA.
    if (!createNodeMem(&q)) { //SI NO HAY NODO SE RETORNA FALSO.
        return false;
    } else {
        if(tipo==1||tipo==3){
        q->address=dirrecion;
        q->size=tamano;
        q->tipo=tipo;
        q->time=t;
        q->next = LNULL;
        }else{
            q->address=dirrecion;
            q->size=tamano;
            q->tipo=tipo;
            q->time=t;
            q->next = LNULL;
            q->id=df;
            strcpy(q->fich,nombre);
        }
        if (L->next == LNULL) { //LISTA VACÍA.
            L->next = q;
        } else{
            for(p=L->next;p->next!=NULL;p=p->next);
            p->next=q;
        }
        return true;
    }
}
char *ptr2string( const void *ptr ) {
    int size = snprintf( NULL, 0, "%p", ptr );
    char *result = calloc( size + 1, 1 );
    sprintf( result, "%p", ptr );
    return result;
}

pos EncontrarPosicion(MemoryList Lista, char* direccion) {
    pos p;
    for (p = Lista->next; (p != NULL) && strcmp(ptr2string(p->address), direccion)<0; p = p->next);
    return p;

}

pos EncontrarTamano(MemoryList Lista, long tamano) {
    pos p;
    for (p = Lista->next; (p != NULL) && p->size!=tamano; p = p->next);
    return p;

}
void deleteAtPosition (pos p, MemoryList L) {
    pos q;
    if (p == L->next) { //ELIMINAR ELEMENTO DEL INICIO.
        L = L->next->next;
    } else if (p->next == LNULL) { //ELIMINAR ELEMENTO DEL FINAL.
        for (q = L; q->next != p; q = q->next);
        q->next = LNULL;

    } else { //ELIMINAR ELEMENTO DEL MEDIO.
        q = p->next;
        strcpy(p->parms,p->parms);
        strcpy(p->fich,p->fich);
        p->address=q->address;
        p->size=q->size;
        p->tipo=q->tipo;
        p->time=q->time;
        p->id=q->id;
        p->next = q->next;
        p = q;
    }
    free(p);

}
char* getAdrres(pos p){
     return p->address;
}
