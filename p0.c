#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <direct.h>

#include <time.h>
/*#include "linklist_headnode.h"*/
#define N 48
void leerEntrada(char cadena);
int TrocearCadena(char *cadena, char *trozos[]);
int ProcesarEntrada(char *trozos[], int ntrozos);
void imprimirPrompt();
//ESTO SERÍA EN OTRO MAIN.C
int doautores(char *param[]);
int dopid(char *param[]);
int dohist(char *param[]);
int docarpeta(char *param[]);
int docomando(char *param[]);
int dofecha(char *param[]);
int doexit(char *param[]);
int doquit(char *param[]);


int main (){
    int salir=0;
    char cadena[N] ;
    char *trozos[N/2];


    while ( salir!= 1){
        imprimirPrompt();
        leerEntrada(*cadena);
        int ntrozos= TrocearCadena(cadena, trozos);
        salir=ProcesarEntrada(trozos, ntrozos);
        // aqui pondria un if para si el int que te devuelve no es el numero que le ponemos a hist y al comando n se guarde en la lista de comando
    }
}

void leerEntrada(char cadena){

    fgets(&cadena, N, stdin );
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

void imprimirPrompt(){
    printf("$ ");
}

int ProcesarEntrada(char * trozos[], int ntrozos){
    char **param=trozos;
    int i=0;
    if (param[0]==NULL){return 0;}
    if(strcmp(param[0], "autores")==0){
        return doautores(param);
    }else if(strcmp(param[0], "pid")==0){
        return dopid(param);
    }else if(strcmp(param[0], "carpeta")==0){
        return docarpeta(param);
    }else if(strcmp(param[0], "fecha")==0){
        return dofecha(param);
    }else if(strcmp(param[0], "hist")==0){
        return dohist(param);
    }else if(strcmp(param[0], "comando")==0){
        return docomando(param);
    }else if(strcmp(param[0], "exit")==0){
        return doexit(param);
    }else if(strcmp(param[0], "comando")==0){
    return doquit(param);

    }else {
        printf("\nEste comando no existe\n");
    }
    return 0;
}

int doexit(char *param[]) {
    return -1;
}
int doquit(char *param[]){
    return -1;
}
int doautores(char *param[]) {
    if (param != 0) {
        if (strcmp(param[1], "-l") == 0) { //Imprime el login.
            printf("eloy.sastre@udc.es\n");
            printf("daniel.pmosquera@udc.es\n");
        } else if (strcmp(param[1], "-n") == 0) { //Imprime los nombres.
            printf("Eloy Sastre Sobrino\n");
            printf("Daniel Pérez Mosquera\n");
        }
    }else { //Imprime ambos

            printf("Eloy Sastre Sobrino: eloy.sastre@udc.es\n");
            printf("Daniel Pérez Mosquera: daniel.pmosquera@udc.es\n");
        }
    return 0;
}
int doFecha(char *param[]) {
    time_t tiempoahora;
    time(&tiempoahora);
    struct tm *t=localtime(&tiempoahora);
    //Empieza a contar los meses desde 0, por eso le sumo 1, y los años desde 1900.
    int day=t->tm_mday, month=t->tm_mon+1, year= t->tm_year+1900, hour=t->tm_hour, min=t->tm_min, sec=t->tm_sec;

    if (param != 0) {
        if (strcmp(param[1], "-d") == 0) { //Imprime formato DD/MM//AA
            printf("%d/%d/%d\n", day, month, year); }
        else if (strcmp(param[1], "-h") == 0) { //Imprime formato hh:mm:ss
            printf("%d:%d:%d\n", hour,min,sec);
        }
    }else { //Imprime los dos
        printf("%d/%d/%d  -->", t->tm_mday, t->tm_mon, t->tm_year);
        printf("%d:%d:%d\n", t->tm_hour, t->tm_min, t->tm_sec);
    }
    return 0;
}

int dopid(char *param[]){
    int pid,p_pid;
    pid=getpid();
    p_pid=getppid();

    if (param != 0) {
        if (strcmp(param[1], "-p") == 0) { //proceso padre
            printf("Proceso padre del shell: %d\n", p_pid);
        }
    }
    else { //proceso hijo
        printf("Proceso del shell: %d\n", pid);

    }
    return 0;

}

int docarpeta (char *param[]){
    char buffer [1024];
    if (_getcwd(buffer,1024)==NULL){
    printf("Get current working directory fail");
return 1;}
    else{
        printf("Current working directory: \n %s \n", buffer);
    }

    if (param != 0) {
        if (strcmp(param[1], "direct") == 0) {
        }
    }
    else {

    }

}


