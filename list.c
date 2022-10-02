
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
    return &p->datos; //RETORNA LvOS DATOS DE LA POSICIÓN QUE SE INTRODUCE.
}

void printList(tList *L){
    tPosL p;
    int i=1;
    for(p=p->next;p->next!=NULL;p=p->next){
        printf("%d->%s",i, getChar(p,*L));
        i++;
    }
}


bool insertItem(char d, tList L) {
    tPosL p, q; //LAS VARIABLES 'r' Y 'q' ACTUÁN COMO NODOS PARA APUNTAR AL NODO QUE QUEREMOS INTRODUCIR EN LA LISTA.
    if (!createNode(&q)) { //SI NO HAY NODO SE RETORNA FALSO.
        return false;
    } else {
        q->datos = d;
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



void printn(char* param[],tList L){
    tPosL p;
    int counter=0;
    for(p=L->next;p->next!=NULL;p=p->next){
        counter++;
    }
    long n= strtol(param[1],LNULL,10); // teoricamente transforma el char en un int lo busque en internet
    p=L->next;
    if(n<=counter) {
        for (int i = 0; i < n; i++) {
            p = p->next;
            printf("%s", getChar(p, L));
        }
    }else{
        printf("No hay este número de elementos");
    }
}

void deleteAtPosition (tPosL p, tList *L) {
    tPosL q;
    if (p->next == LNULL) { //ELIMINAR ELEMENTO DEL FINAL.
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


