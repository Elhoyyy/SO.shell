
//
// Created by elhoyyy on 25/11/22.
//

#include "headed_linked_joblist.h"


void createJobList(JobList * L){
    posJ cabeceira;
    cabeceira=malloc(sizeof(**L));
    *L=cabeceira;
    cabeceira->next=NULL;
}

bool createNodeJob( posJ* p){
    *p= malloc(sizeof(**p));
    return *p!=NULL;
}

bool insertJobList(JobList L, int pid, char* status, int priority , char *lineacomnando, time_t tiempo, uid_t  uid){
    posJ p, q; //LAS VARIABLES 'r' Y 'q' ACTUÁN COMO NODOS PARA APUNTAR AL NODO QUE QUEREMOS INTRODUCIR EN LA LISTA.

    if (!createNodeJob(&q)) //SI NO HAY NODO SE RETORNA FALSO.
        return false;
    q->pid=pid;
    q->status=status;
    q->priority=priority;
    strcpy(q->lineacomando,lineacomnando);
    q->time=tiempo;
    q->uid=uid;
    q->next = NULL;
    if (L->next == NULL) { //LISTA VACÍA.
        L->next = q;
    } else{
        for(p=L->next;p->next!=NULL;p=p->next);
        p->next=q;
    }
    return true;
}
void deleteAtJPosition (posJ p, JobList L) {
    posJ q;
    if (p == L->next) { //ELIMINAR ELEMENTO DEL INICIO.
        L->next=p->next;
    } else if (p->next == NULL) { //ELIMINAR ELEMENTO DEL FINAL.
        for (q = L; q->next != p; q = q->next);
        q->next = NULL;

    } else { //ELIMINAR ELEMENTO DEL MEDIO.
        q = p->next;
        strcpy(p->lineacomando,q->lineacomando);
        p->pid=q->pid;
        p->status=q->status;
        p->priority=q->priority;
        p->time=q->time;
        p->next = q->next;
        p->uid = q->uid;

        p = q;
    }
    free(p);

}
