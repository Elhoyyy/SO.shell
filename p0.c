
#include "headed_linked_list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/syscall.h>
#include <time.h>

#define N 48

void leerEntrada(char cadena);
int TrocearCadena(char *cadena, char *trozos[]);
int ProcesarEntrada(char *trozos[]);
void imprimirPrompt();
//ESTO SERÍA EN OTRO MAIN.C
int doautores(char *param[]);
int dopid(char *param[]);
int dohist(char *param[]);
int docarpeta(char *param[]);
int docomando(char *param[]);
int dofecha(char *param[]);
int doexit();
int dosalir();
int dobye();
int doinfosis(char *param[]);
int doayuda(char *param[]);
char * infoparametros(char *cmd);

int main (){
    int acabar=0;
    char cadena[N] ;
    char *trozos[N/2];
    tList Lista;
    createList(&Lista);


    while ( !acabar){
        imprimirPrompt();
        leerEntrada(*cadena);
        insertItem(cadena,&Lista);
        int ntrozos= TrocearCadena(cadena, trozos);
        acabar=ProcesarEntrada(trozos);
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

void imprimirPrompt(){
    printf("$ ");
}

int ProcesarEntrada(char * trozos[]){
    char **param=trozos;
    int i=0;
    if (param[0]==NULL){return i;}
    if(strcmp(param[0], "autores")==0){
        i=doautores(param);
    }else if(strcmp(param[0], "pid")==0){
        i=dopid(param);
    }else if(strcmp(param[0], "carpeta")==0){
        i=docarpeta(param);
    }else if(strcmp(param[0], "fecha")==0){
        i=dofecha(param);
    }else if(strcmp(param[0], "hist")==0){
        //dohist(param);
    }else if(strcmp(param[0], "comando")==0){
        //docomando(param,);
    }else if(strcmp(param[0], "salir")==0){
        i=dosalir();

    }else if(strcmp(param[0], "exit")==0){
        i=doexit();

    }else if(strcmp(param[0], "bye")==0){
        i=dobye();

    }else if(strcmp(param[0], "infosis")==0){
        i=doinfosis(param);

    }else if(strcmp(param[0], "ayuda")==0){
        i=doayuda(param);

    }else {
        printf("\nEste comando no existe\n");
    }
    return i;
}

int doexit() {
    return 0;
    ;}
int dobye() {
    return 0;
}
int dosalir(){
    return 0;
}
int doautores(char *param[]) {
    if (param[1] != NULL) {
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
    return 1;
}
int doFecha(char *param[]) {
    time_t tiempoahora;
    time(&tiempoahora);
    struct tm *t=localtime(&tiempoahora);
    //Empieza a contar los meses desde 0, por eso le sumo 1, y los años desde 1900.
    int day=t->tm_mday, month=t->tm_mon+1, year= t->tm_year+1900, hour=t->tm_hour, min=t->tm_min, sec=t->tm_sec;

    if (param[1] != NULL) {
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
    return 1;

}

int doinfosis(char *param[]){
    struct utsname info;
    if(!uname(&info)){
        printf("%s(%s), OS: %s-%s-%s \n", info.nodename,info.machine, info.sysname, info.release, info.version);
    }
    return 1;
}

struct t_ayuda{
    char* cmd;
    char* msg;
};
char * infoparametros(char * cmd){
    static struct t_ayuda V[11];

    V[0].cmd="ayuda";
    V[1].cmd="bye";
    V[2].cmd="exit";
    V[3].cmd="salir ";
    V[4].cmd="infosis ";
    V[5].cmd="comando ";
    V[6].cmd="hist";
    V[7].cmd="autores";
    V[8].cmd="fecha";
    V[9].cmd="pid ";
    V[10].cmd="carpeta";

    V[0].msg="ayuda [cmd]	Muestra ayuda sobre los comandos";
    V[1].msg="bye 	Termina la ejecucion del shell";
    V[2].msg="exit";
    V[3].msg="salir 	Termina la ejecucion del shell 	Termina la ejecucion del shell";
    V[4].msg="infosis 	Muestra informacion de la maquina donde corre el shell";
    V[5].msg="comando [-N]	Repite el comando N (del historico)";
    V[6].msg="hist [-c|-N]	Muestra el historico de comandos, con -c lo borra";
    V[7].msg="autores [-n|-l]	Muestra los nombres y logins de los autores";
    V[8].msg="fecha [-d|.h	Muestra la fecha y o la hora actual";
    V[9].msg="pid [-p]	Muestra el pid del shell o de su proceso padre";
    V[10].msg="carpeta [dir]	Cambia (o muestra) el directorio actual del shell";


    int i;
    for (i=0; i<11; i++)
        if (strcmp(V[i].cmd, cmd) ==0)
            break;
    if (i==11) return "";
    return V[i].msg;

}

int doayuda(char *param[]) {

    if (param[1]!= NULL) {
        infoparametros(param[1]);

    } else {
        printf("'ayuda cmd' donde cmd es uno de los siguientes comandos:fin salir bye fecha pid autores hist comando carpeta infosis ayuda");

        printf("\n");
    }
    return 1;
}

int dopid(char *param[]){
    int pid,p_pid;
    pid=getpid();
    p_pid=getppid();

    if (param[1] != NULL) {
        if (strcmp(param[1], "-p") == 0) { //proceso padre
            printf("Proceso padre del shell: %d\n", p_pid);
        }
    }
    else { //proceso hijo
        printf("Proceso del shell: %d\n", pid);

    }
    printf("\n");
    return 1;


}

int docarpeta (char *param[]){
    if (param[1] != NULL) {
            if((chdir(*param)==-1)){
                perror("No se pudo cambiar el directorio");

            }

    }
    else {//Imprime el directorio actual.
        char *currentDir= getcwd(NULL,0);
        printf("\nPWD==>%s",currentDir);
        free(currentDir);

    }        printf("\n");

    return 1;
}

int doHist(char* param[],tList Lista){return 0;}
/*
int doHist2(char* param[],tList Lista){
    if(param[1]!=NULL){
        if(strcmp(param[1],"-c")==0){
            tPosL k;
            for(k=Lista;k->next!=NULL;k=k->next){
                deleteAtPosition(k,&Lista);
            }
        }else{
            printn(param[1],Lista);
        }

    }else{
        printList(Lista);
    }
    return 1;
}
 */
int doComandoN(char* param[],tList L){ return 0;}
/*
int doComandoN2(char* param[],tList L){
    tPosL p;
    char copy[N];
    char *trozoscopy[N/2];
    long n= strtol(*param,NULL,10); // teoricamente transforma el char en un int lo busque en internet
    p=L;
    for(int i=0;i<n;i++){
        p=p->next;
    }
    strcpy(copy, getChar(p, L));
    printf("%s",copy);
    int ntrozos= TrocearCadena(copy, trozoscopy);
    ProcesarEntrada(trozoscopy);
    return 1;
}*
