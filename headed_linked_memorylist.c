

#include <sys/stat.h>
#include "headed_linked_memorylist.h"
#include "headed_linked_list.h"

void InsertarNodoMmap(tList ListaMemoria, int tipo, void * p, long int st_size, char * fichero){
    char fecha[50];
    if(tipo==1){
        struct malloc_t *mallc= malloc(sizeof (struct malloc_t));
        mallc->tamano=st_size;
        mallc->address=p;
        time_t actual;
        strftime(fecha, 30, "%a %b %d %T %Y", localtime (&actual));
        insertItem((char *) mallc, ListaMemoria);

    }else if(tipo==2){
        struct mmap_t* mmap= malloc((sizeof (struct mmap_t)));
        mmap->tamano=st_size;
        mmap->address=p;
        strcpy(mmap->name,fichero);
        time_t actual;
        strftime(fecha, 30, "%a %b %d %T %Y", localtime (&actual));
        insertItem((char *) mmap, ListaMemoria);

    }
    else {
        struct shared_t *shared= malloc(sizeof (struct shared_t));
        shared->address=p;
        shared->tamano=st_size;
        time_t actual;
        strftime(fecha, 30, "%a %b %d %T %Y", localtime (&actual));
        insertItem((char *) shared, ListaMemoria);
    }
}

void *getAdrress(tList L,tPosL p){
    if(p==NULL){
        return NULL;
    }
    else{
        return p->datos;
    }
}


void deleteAtPosition (tPosL p, tList* L) {
    tPosL q;
    q = (*L)->next;
    if (p == (*L)->next) { //ELIMINAR ELEMENTO DEL INICIO.
        (*L)->next = (*L)->next;
    } else if (p->next == LNULL) { //ELIMINAR ELEMENTO DEL FINAL.
        for (q = (*L)->next; q->next != p; q = q->next);
        q->next = LNULL;

    } else { //ELIMINAR ELEMENTO DEL MEDIO.
        q = p->next;
        strcpy((p->datos), q->datos);
        p->next = q->next;
        p = q;
    }
    free(p->datos);
    free(p);

}

void printListaMememoria(tList L, int tipo){
    tPosL p;

    if(tipo == 1) {
        for (p = L->next; p->next != NULL; p = p->next) {
            struct malloc_t *malloc = getAdrress(L->next, p);
            //PONER EL TIEMPO
            printf("\t%p %d %s ", malloc->address, malloc->tamano, malloc->time);
            printf("malloc\n");
        }
    }
    if(tipo == 2) {
        for (p = L->next; p->next != NULL; p = p->next) {

            struct mmap_t *mmap = getAdrress(L->next, p);
            //TIEMPO
            printf("\t%p %d %s ", mmap->address, mmap->tamano, mmap->time);
            printf("mmap %s (fd:%d)\n", mmap->name, mmap->id);
        }
    }
    if(tipo == 3) {
        for (p = L->next; p->next != NULL; p = p->next) {
            struct shared_t *shared = getAdrress(L->next, p);
            //TIEMPO
            printf("\t%p %d %s ", shared->address, shared->tamano, shared->time);
            printf("shared memory with key: %d\n",shared->key);
        }
    }
}
