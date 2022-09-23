//
// Created by danip on 22/09/2022.
//

#include "list.h"
void createList(tList* L){
    *L=LNULL;
    head=*L ;
}

bool createNode( tPosL* p){
    *p= malloc(sizeof(**p));
    return *p!=LNULL;
}



char getChar( tPosL p, tList L){
    return p->datos; //RETORNA LvOS DATOS DE LA POSICIÓN QUE SE INTRODUCE.
}

void printList(tList L){
    tPosL p;
    for(p=L;p->next!=NULL;p=p->next){
        printf("%c",getChar(p,L));
    }
}

tPosL findPosition(tList L, char* d) {
    tPosL p;
    for (p = L; (p != NULL) && strcmp(&p->datos, d)<0; p = p->next);
    return p;

}

bool insertItem(char* d, tList *L) {
    tPosL p, q, r; //LAS VARIABLES 'r' Y 'q' ACTUÁN COMO NODOS PARA APUNTAR AL NODO QUE QUEREMOS INTRODUCIR EN LA LISTA.
    if (!createNode(&q)) { //SI NO HAY NODO SE RETORNA FALSO.
        return false;
    } else {
        q->datos = *d;
        q->next = LNULL;
        if (*L == LNULL) { //LISTA VACÍA.
            *L = q;
        } else if (strcmp(*d, &((*L)->datos))<0) { //INSERTAR EN EL FINAL.
            q->next = *L;
            *L = q;
        } else {
            p = findPosition(*L, d);
            if (p == LNULL) {
                for (r = *L; r->next != LNULL; r = r->next);
                r->next = q;
            } else {
                q->datos = p->datos;
                p->datos = *d;
                q->next = p->next;
                p->next = q;
            }
        }
        return true;
    }
}


void printn(char* param[],tList L){
    tPosL p;
    long n= strtol(*param,NULL,10); // teoricamente transforma el char en un int lo busque en internet
    p=L;
    for(int i=0;i<n;i++){
        p=p->next;
    printf("%c", getChar(p,L));
       }
}

void deleteAtPosition (tPosL p, tList *L) {
    tPosL q;
    if (p == *L) { //ELIMINAR ELEMENTO DEL INICIO.
        *L = (*L)->next;
    } else if (p->next == LNULL) { //ELIMINAR ELEMENTO DEL FINAL.
        for (q = *L; q->next != p; q = q->next);
        q->next = LNULL;

    } else { //ELIMINAR ELEMENTO DEL MEDIO.
        q = p->next;
        p->datos = q->datos;
        p->next = q->next;
        p = q;
    }
    free(p);

}
