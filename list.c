
#include "headed_linked_list.h"
void createList(tList* L){
    tPosL cabeceira;
    cabeceira=malloc(sizeof(**L));
    *L=cabeceira;
    cabeceira->next=NULL;
}

bool createNode( tPosL* p){
    *p= malloc(sizeof(**p));
    return *p!=LNULL;
}



char* getChar( tPosL p, tList L){
    return p->datos; //RETORNA LvOS DATOS DE LA POSICIÓN QUE SE INTRODUCE.
}

void printList(tList L){
    tPosL p;
    int i=1;
    for(p=L->next;p->next!=NULL;p=p->next){
        printf("%d->%s",i, getChar(p,L));
        i++;
    }
}


bool insertItem(char * d, tList L) {
    tPosL p, q; //LAS VARIABLES 'r' Y 'q' ACTUÁN COMO NODOS PARA APUNTAR AL NODO QUE QUEREMOS INTRODUCIR EN LA LISTA.
    if (!createNode(&q)) { //SI NO HAY NODO SE RETORNA FALSO.
        return false;
    } else {
        strcpy(q->datos, d);
        q->next = LNULL;
        if (L->next == LNULL) { //LISTA VACÍA.
            L->next = q;
        } else{
            for(p=L->next;p->next!=NULL;p=p->next);
            p->next=q;
        }
        return true;
    }
}



void deleteList (tList L){
    tPosL q, p ;
    q=L->next;
    while(q!=NULL){
        p=q;
        q=q->next;
        free (p);

    }
    L->next=NULL;
}


