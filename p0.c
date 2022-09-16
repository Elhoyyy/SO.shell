#include <stdio.h>
#include <string.h>
#include "linklist_headnode.h"
#define N 48
void leerEntrada(char cadena);
int TrocearCadena(char *cadena, char *trozos[]);
int ProcesarEntrada(char *trozos[], int ntrozos);
void imprimirPrompt();


int main (){
    int salir=0;
    char cadena[N] ;
    char *trozos[N/2];


    while ( salir!= 1){
        imprimirPrompt();
        leerEntrada(cadena);
        int ntrozos= TrocearCadena(cadena, trozos);
        salir=ProcesarEntrada(trozos, ntrozos);
        // aqui pondria un if para si el int que te devuelve no es el numero que le ponemos a hist y al comando n se guarde en la lista de comando
    }
}

void leerEntrada(char cadena){

    fgets(cadena, N, stdin );
    // return x;
}


int TrocearCadena(char * cadena, char * trozos[])
{ int i=1;
    if ((trozos[0]=strtok(cadena," \n\t"))==NULL)
        return 0;
    while ((trozos[i]=strtok(NULL," \n\t"))!=NULL)
        i++;
    return i;
}

int ProcesarEntrada(char * trozos[], int ntrozos){

}

void imprimirPrompt(){
    printf("$ ");
}

