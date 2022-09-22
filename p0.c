#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/utsname.h>
#include <time.h>

/*#include "linklist_headnode.h"*/
#define N 48

void leerEntrada(char cadena);
int TrocearCadena(char *cadena, char *trozos[]);
void ProcesarEntrada(char *trozos[], int ntrozos);
void imprimirPrompt();
//ESTO SERÍA EN OTRO MAIN.C
void doautores(char *param[]);
void dopid(char *param[]);
void dohist(char *param[]);
void docarpeta(char *param[]);
int docomando(char *param[]);
void dofecha(char *param[]);
void doexit(char *param[]);
void dosalir(char *param[]);
void dobye(char *param[]);
void doinfosis(char *param[]);
void doayuda(char *param[]);

int main (){
    int acabar=0;
    char cadena[N] ;
    char *trozos[N/2];


    while ( !acabar){
        imprimirPrompt();
        leerEntrada(*cadena);
        int ntrozos= TrocearCadena(cadena, trozos);
        ProcesarEntrada(trozos, ntrozos);
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

void ProcesarEntrada(char * trozos[], int ntrozos){
    char **param=trozos;
    int i=0;
    if (param[0]==NULL){exit(0);}
    if(strcmp(param[0], "autores")==0){
         doautores(param);
    }else if(strcmp(param[0], "pid")==0){
         dopid(param);
    }else if(strcmp(param[0], "carpeta")==0){
         docarpeta(param);
    }else if(strcmp(param[0], "fecha")==0){
         dofecha(param);
    }else if(strcmp(param[0], "hist")==0){
         //dohist(param);
    }else if(strcmp(param[0], "comando")==0){
         //docomando(param,);
    }else if(strcmp(param[0], "salir")==0){
         dosalir(param);

    }else if(strcmp(param[0], "exit")==0){
         doexit(param);

    }else if(strcmp(param[0], "bye")==0){
         dobye(param);

    }else if(strcmp(param[0], "infosis")==0){
         doinfosis(param);

    }else if(strcmp(param[0], "ayuda")==0){
     doayuda(param);

    }else {
        printf("\nEste comando no existe\n");
    }

}

void doexit(char *param[]) {
    exit(0)
;}
void dobye(char *param[]) {
    exit(0);
}
void dosalir(char *param[]){
    exit(0);
}
void doautores(char *param[]) {
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
    printf("\n");

}
void doFecha(char *param[]) {
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
        printf("%d/%d/%d  --> " , day, month, year);
        printf("%d:%d:%d\n", hour,min,sec);
    }
    printf("\n");

}

void doinfosis(char *param[]){
    struct utsname info;
    if(!uname(&info)){
        printf("%s(%s), OS: %s-%s-%s \n", info.nodename,info.machine, info.sysname, info.releasem, info.version);
    }
}
void xDDD(char *param[]){

}
void xDDD2(char *param []){

}

void doayuda(char*param[],){
    if(**param!=0){
        if(strcmp(param[1],"cmd")==0){

        }else{

            printf("\nLista de comandos: ");

            printf("autores[-l][-n]\tpid[-p]\tcarpeta[direct]\tfecha[-d][-h]\thist[-c][-N]\tcomando N(número de comando)\tinfosis\tayuda[cmd]\n");
            /*for(int i=0;i<**param;i++){
                printf("%c", *param[i]);
            }*/
        }
        printf("\n");
    }
}

void dopid(char *param[]){
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
    printf("\n");


}

void docarpeta (char *param[]){
    char *currentDir [1024];
    if (param != 0) {
        if (strcmp(param[1], "direct") == 0) {

        }
    }
    else {//Imprime el directorio actual.
        char *currentDir= getcwd(NULL,0);
        printf("\nPWD==>%s",currentDir);

    }        printf("\n");


}
/*int hist(**param, ){
}

int comando(**param, ){}
/*


