/*TITULO:
SISTEMAS OPERATIVOS Práctica 1
AUTOR 1: Eloy Sastre Sobrino LOGIN 1: eloy.sastre
AUTOR 2: Daniel Pérez Mosquera LOGIN 2: daniel.pmosquera
GROUP: 1.1
DATE: 20/10/2022
*/

#include "headed_linked_list.h"
#include "headed_linked_memorylist.h"
#include "headed_linked_joblist.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/resource.h>

#define MALLOC 1
#define SHARED 2
#define MMAP 3
#define N 48
#define TAMANO 2048

/*************************************************************/

/*las siguientes funciones nos permiten obtener el nombre de una senal a partir
del número y viceversa */
struct SEN {
    char * nombre;
    int  senal;
};

static struct SEN sigstrnum[]={
        {"HUP", SIGHUP},
        {"INT", SIGINT},
        {"QUIT", SIGQUIT},
        {"ILL", SIGILL},
        {"TRAP", SIGTRAP},
        {"ABRT", SIGABRT},
        {"IOT", SIGIOT},
        {"BUS", SIGBUS},
        {"FPE", SIGFPE},
        {"KILL", SIGKILL},
        {"USR1", SIGUSR1},
        {"SEGV", SIGSEGV},
        {"USR2", SIGUSR2},
        {"PIPE", SIGPIPE},
        {"ALRM", SIGALRM},
        {"TERM", SIGTERM},
        {"CHLD", SIGCHLD},
        {"CONT", SIGCONT},
        {"STOP", SIGSTOP},
        {"TSTP", SIGTSTP},
        {"TTIN", SIGTTIN},
        {"TTOU", SIGTTOU},
        {"URG", SIGURG},
        {"XCPU", SIGXCPU},
        {"XFSZ", SIGXFSZ},
        {"VTALRM", SIGVTALRM},
        {"PROF", SIGPROF},
        {"WINCH", SIGWINCH},
        {"IO", SIGIO},
        {"SYS", SIGSYS},
/*senales que no hay en todas partes*/
#ifdef SIGPOLL
        {"POLL", SIGPOLL},
#endif
#ifdef SIGPWR
        {"PWR", SIGPWR},
#endif
#ifdef SIGEMT
        {"EMT", SIGEMT},
#endif
#ifdef SIGINFO
        {"INFO", SIGINFO},
#endif
#ifdef SIGSTKFLT
        {"STKFLT", SIGSTKFLT},
#endif
#ifdef SIGCLD
        {"CLD", SIGCLD},
#endif
#ifdef SIGLOST
        {"LOST", SIGLOST},
#endif
#ifdef SIGCANCEL
        {"CANCEL", SIGCANCEL},
#endif
#ifdef SIGTHAW
        {"THAW", SIGTHAW},
#endif
#ifdef SIGFREEZE
        {"FREEZE", SIGFREEZE},
#endif
#ifdef SIGLWP
        {"LWP", SIGLWP},
#endif
#ifdef SIGWAITING
        {"WAITING", SIGWAITING},
#endif
        {NULL,-1},
};    /*fin array sigstrnum */


int ValorSenal(char * sen)  /*devuelve el numero de senial a partir del nombre*/
{
    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++)
        if (!strcmp(sen, sigstrnum[i].nombre))
            return sigstrnum[i].senal;
    return -1;
}


char *NombreSenal(int sen)  /*devuelve el nombre senal a partir de la senal*/
{			/* para sitios donde no hay sig2str*/
    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++)
        if (sen==sigstrnum[i].senal)
            return sigstrnum[i].nombre;
    return ("SIGUNKNOWN");
}




/********************************************/

void leerEntrada(char *cadena);
int TrocearCadena(char *cadena, char *trozos[]);
int ProcesarEntrada(char *trozos[],tList Lista,MemoryList Listamemoria, JobList Listajobs);
void imprimirPrompt();
int doautores(char *param[]);
int dopid(char *param[]);
int dohist(char *param[],tList Lista);
int docarpeta(char *param[]);
int dofecha(char *param[]);
int doexit();
int dosalir();
int dobye();
int doinfosis(char *param[]);
int doayuda(char *param[]);
char * infoparametros(char *cmd);
char *NombreSenal(int sen);
int deljobs (char *param[], JobList L);
int doayuda(char *param[]);
int dostats(char *param[]);
int dolist(char *param[]);
int dodelete(char *param[]);
int dodeltree(char *param[]);
int docreate(char *param[]);
int docomando (char *param[], tList Lista,MemoryList Listamemoria, JobList Listajobs);
int doallocate(char *param[],MemoryList Listamemoria);
int dodeallocate(char *param[],MemoryList Listamemoria);
int doinout(char *param[]);
int domemfill(char *param[]);
int domemory(char *param[],MemoryList listamemoria);
int domemdump(char *param[]);
int dorecurse(char *param[]);
void tipostatus (posJ p);
int job ( char * param[], JobList L);

void borrar_recursivo(char * dir);
void ListarDirectorio(char *dir,int hid,int l,int acc,int link);
void procesardirectorioA(char *dir,int hid,int l,int acc,int link, int reca,int recb);
void do_AllocateMalloc(MemoryList listaMemoria,long tamano);
void printListaMememoria(MemoryList L, int tipo);
void LlenarMemoria (void *p, size_t cont, unsigned char byte);
void do_AllocateMmap(char *arg[],MemoryList listamemoria);
void do_AllocateCreateshared (char *tr[],MemoryList Listamemoria);
void Recursiva (int n);
void do_I_O_read (char *ar[]);
void do_DeallocateDelkey (char *args[]);
ssize_t EscribirFichero (char *f, void *p, size_t cont,int overwrite);
void do_I_O_write (char *ar[]);
void Do_pmap (void);
void do_AllocateShared (char *tr[],MemoryList Listamemoria);
int dopriority ( char *param[]);
int dofork ( char *param[]);
int dolistjobs ( char *param[], JobList L);
int doshowvar ( char * param []);
int dochangevar(char* param[]);
int OurExecvpe(char *file, char *const argv[], char *const envp[]);
void MuestraEntorno ( char *entorno[], char *nombre_variable);
int BuscarVariable(char* variable,char* entorno[]);
int CambiarVariable(char * var, char * valor, char *e[]);
int doshowenv(char *param[]);
char * Ejecutable (char *s);
int doexecute(char* param[],JobList L);
int puntos(char *param[],JobList L);

char **puntero;

int main(int arg,char *argv[], char *env[]){
    int acabar=0;
    char cadena[N] ;
    char *trozos[N/2];
    tList Lista;
    createList(&Lista);
    MemoryList Listamemoria;
    createMemoryList(&Listamemoria);
    JobList  Listajobs;
    createJobList(&Listajobs);

    puntero=env;


    while ( acabar!=-1 ){

        imprimirPrompt();
        leerEntrada(cadena);
        insertItem(cadena,Lista);
        TrocearCadena(cadena, trozos);
        acabar=ProcesarEntrada(trozos,Lista,Listamemoria, Listajobs);

    }

    deleteList(Lista);
    free (Lista);
    deleteMemorylist(Listamemoria);
    free(Listamemoria);
    return 1;
}

char  LetraTF (mode_t m)
{
    switch (m&S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK: return 'l'; /*symbolic link*/
        case S_IFREG: return '-'; /* fichero normal*/
        case S_IFBLK: return 'b'; /*block device*/
        case S_IFDIR: return 'd'; /*directorio */
        case S_IFCHR: return 'c'; /*char device*/
        case S_IFIFO: return 'p'; /*pipe*/
        default: return '?'; /*desconocido, no deberia aparecer*/
    }
}

char *  ConvierteModo2 (mode_t m)
{
    static char permisos[12];
    strcpy (permisos,"---------- ");

    permisos[0]=LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r';    /*propietario*/
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r';    /*grupo*/
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r';    /*resto*/
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s';    /*setuid, setgid y stickybit*/
    if (m&S_ISGID) permisos[6]='s';
    if (m&S_ISVTX) permisos[9]='t';

    return permisos;
}



void leerEntrada(char *cadena){

    fgets(cadena, N, stdin );

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
    printf("$");
}

int ProcesarEntrada(char * trozos[],tList Lista,MemoryList Listamemoria, JobList Listajobs){
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
        i=dohist(param,Lista);
    }else if(strcmp(param[0], "comando")==0){
        i=docomando(param,Lista,Listamemoria, Listajobs);
    }else if(strcmp(param[0], "salir")==0){
        i=dosalir();
    }else if(strcmp(param[0], "exit")==0){
        i=doexit();

    }else if(strcmp(param[0], "bye")==0){
        i=dobye();

    }else if(strcmp(param[0], "infosis")==0){
        i=doinfosis(param);

    }else if(strcmp(param[0], "ayuda")==0) {
        i = doayuda(param);
    }else if(strcmp(param[0], "stats")==0) {
        i = dostats(param);
    }else if(strcmp(param[0], "list")==0) {
        i = dolist(param);
    }else if(strcmp(param[0], "create")==0) {
        i = docreate(param);
    }else if(strcmp(param[0], "delete")==0){
        i=dodelete(param);
    }else if(strcmp(param[0], "deltree")==0){
        i=dodeltree(param);

    }else if(strcmp(param[0], "deltree")==0){
        i=dodeltree(param);

    }else if(strcmp(param[0], "allocate")==0){
        i=doallocate(param,Listamemoria);

    }else if(strcmp(param[0], "deallocate")==0){
        i=dodeallocate(param,Listamemoria);

    }else if(strcmp(param[0], "i-o")==0){
        i=doinout(param);

    }else if(strcmp(param[0], "memfill")==0){
        i=domemfill(param);

    }else if(strcmp(param[0], "memdump")==0){
        i=domemdump(param);

    }else if(strcmp(param[0], "memory")==0){
        i=domemory(param,Listamemoria);

    }else if(strcmp(param[0], "recurse")==0) {
        i = dorecurse(param);

    }else if ( strcmp (param[0], "priority") == 0 ){
        i = dopriority (param);
    }else if(strcmp(param[0], "showvar")==0){
        i = doshowvar (param);

    }else if(strcmp(param[0], "changevar")==0){
        i = dochangevar (param);

    }else if(strcmp(param[0], "showenv")==0){
        i = doshowenv (param);

    }else if(strcmp(param[0], "listjobs")==0){
        i = dolistjobs (param, Listajobs);

    }else if(strcmp(param[0], "deljobs")==0){
        i = deljobs (param, Listajobs);

    }else if(strcmp(param[0], "job")==0){
        i = job (param, Listajobs);

    }else if(strcmp(param[0], "execute")==0){
        i = doexecute (param,Listajobs);

    }else if(strcmp(param[0], "fork")==0){
        i = dofork (param);

    }else {
        i= puntos(param,Listajobs);
    }
    return i;
}

int doexit() {
    return -1;
}
int dobye() {
    return -1;
}
int dosalir(){
    return -1;
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
int dofecha(char *param[]) {
    time_t tiempoahora;
    time(&tiempoahora);
    struct tm *t=localtime(&tiempoahora);
    //Empieza a contar los meses desde 0, por eso le sumo 1, y los años desde 1900.
    int day=t->tm_mday, month=t->tm_mon+1, year= t->tm_year+1900, hour=t->tm_hour, min=t->tm_min, sec=t->tm_sec;

    if (param[1] != NULL) {
        if (strcmp(param[1], "-d") == 0) { //Imprime formato DD/MM//AA
            printf("%02d/%02d/%02d\n", day, month, year); }
        else if (strcmp(param[1], "-h") == 0) { //Imprime formato hh:mm:ss
            printf("%02d:%02d:%02d\n", hour,min,sec);
        }
    }else { //Imprime los dos
        printf("%02d/%02d/%02d  --> " , day, month, year);
        printf("%02d:%02d:%02d\n", hour,min,sec);
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

char * infoparametros(char * cmd){

    struct t_ayuda{
        char* cmd;
        char* msg;
    };
    static struct t_ayuda V[33];

    V[0].cmd="ayuda";
    V[1].cmd="bye";
    V[2].cmd="exit";
    V[3].cmd="salir";
    V[4].cmd="infosis";
    V[5].cmd="comando";
    V[6].cmd="hist";
    V[7].cmd="autores";
    V[8].cmd="fecha";
    V[9].cmd="pid";
    V[10].cmd="carpeta";
    V[11].cmd="create";
    V[12].cmd="stat";
    V[13].cmd="list";
    V[14].cmd="delete";
    V[15].cmd="deltree";
    V[16].cmd="allocate";
    V[17].cmd="deallocate";
    V[18].cmd="i-o";
    V[19].cmd="memdump";
    V[20].cmd="memfill";
    V[21].cmd="memory";
    V[22].cmd="recurse";

    V[23].cmd="priority";
    V[24].cmd="showvar";
    V[25].cmd="changevar";
    V[26].cmd="showenv";
    V[27].cmd="fork";
    V[28].cmd="execute";
    V[29].cmd="listjobs";
    V[30].cmd="deljobs";
    V[31].cmd="job";
    V[32].cmd="****";


    V[0].msg="ayuda [cmd]	Muestra ayuda sobre los comandos\n";
    V[1].msg="bye 	Termina la ejecucion del shell\n";
    V[2].msg="exit";
    V[3].msg="salir 	Termina la ejecucion del shell 	Termina la ejecucion del shell\n";
    V[4].msg="infosis 	Muestra informacion de la maquina donde corre el shell\n";
    V[5].msg="comando [-N]	Repite el comando N (del historico)\n";
    V[6].msg="hist [-c|-N]	Muestra el historico de comandos, con -c lo borra\n";
    V[7].msg="autores [-n|-l]	Muestra los nombres y logins de los autores\n";
    V[8].msg="fecha [-d|.h	Muestra la fecha y o la hora actual\n";
    V[9].msg="pid [-p]	Muestra el pid del shell o de su proceso padre\n";
    V[10].msg="carpeta [dir]	Cambia (o muestra) el directorio actual del shell\n";
    V[11].msg="create [-f] [name]	Crea un directorio o un fichero (-f)\n";
    V[12].msg="stat [-long][-link][-acc] name1 name2 ..	lista ficheros;\n"
              "		-long: listado largo\n"
              "		-acc: acesstime\n"
              "		-link: si es enlace simbolico, el path contenido\n";
    V[13].msg="list [-reca] [-recb] [-hid][-long][-link][-acc] n1 n2 ..	lista contenidos de directorios\n"
              "-hid: incluye los ficheros ocultos\n"
              "		-reca: recursivo (antes)\n"
              "		-recb: recursivo (despues)\n"
              "		resto parametros como stat\n";
    V[14].msg="delete [name1 name2 ..]	Borra ficheros o directorios vacios\n";
    V[15].msg="deltree [name1 name2 ..]	Borra ficheros o directorios no vacios recursivamente\n";
    V[16].msg="allocate [-malloc|-shared|-createshared|-mmap] ...\n "
              "Asigna un bloque de memoria\n"
              "-malloc size asigna un bloque malloc de tamano tam\n"
              "-createshared cl tam: asigna (creando) el bloque de memoria compartida de clave cl y tamano tam\n"
              "-shared cl: asigna el bloque de memoria compartida de clave cl\n"
              "-mmap fich perm: mapea el fichero fich, perm son los permisos\n";
    V[17].msg="deallocate [-malloc|-shared|-mmap]..	Desasigna un bloque de memoria\n"
              "-malloc size desasigna el bloque malloc de tamano tam\n"
              "-shared cl: desasigna el bloque de memoria compartida de clave cl\n"
              "-mmap fich: desmapea el fichero mapeado fich\n"
              "addr: desasigna el bloque de memoria en la direccion addr\n";
    V[18].msg="i-o [read|write] [-o] fiche addr cont 	Lee (escribe) cont bytes desde (a) fiche a (desde) addr\n";
    V[19].msg="memdump addr cont 	Vuelca en pantallas los contenidos (cont bytes) de la posicion de memoria addr\n";
    V[20].msg="memfill";
    V[21].msg="memory [-blocks|-funcs|-vars|-all|-pmap] ..	Muestra muestra detalles de la memoria del proceso\n"
              "-blocks: los bloques de memoria asignados\n"
              "-funcs: las direcciones de las funciones\n"
              "-vars: las direcciones de las variables\n"
              ":-all: todo\n"
              "-pmap: muestra la salida del comando pmap(o similar)\n";
    V[22].msg="recurse [n]	Invoca a la funcion recursiva n veces\n";
    V[23].msg="priority [pid] [valor] Muestra o cambia la prioridad del proceso pid a valor\n";
    V[24].msg="showvar Muestra el valor y las direcciones de una variable de entorno\n";
    V[25].msg="changevar [-a|-e|-p] var valor. Cambia el valor de una variable de entorno\n";
    V[26].msg="showenv [-environ|-addr]. Muestra el entorno del proceso\n";
    V[27].msg="fork Hace una llamada fork para crear un proceso\n";
    V[28].msg="execute prog args.... Ejecuta, sin crear proceso,prog con argumentos\n";
    V[29].msg="listjobs Lista los procesos en segundo plano\n";
    V[30].msg="deljobs [-term][-sig] Elimina los propcesos terminados o terminados por senal de la lista de procesos en s.p.\n";
    V[31].msg="job [-fg] pid Muestra informacion del proceso pid. -fg lo pasa a primer plano\n";
    V[32].msg="****\n";

    int i;
    for (i=0; i<33; i++){
        if (strcmp(V[i].cmd, cmd) ==0)
            return V[i].msg;}
    return "";


}

int doayuda(char *param[]) {

    if (param[1]!= NULL) {
        printf("%s",infoparametros(param[1]));

    } else {
        printf("'ayuda cmd' donde cmd es uno de los siguientes comandos:fin salir bye fecha pid autores hist comando carpeta infosis ayuda create stat list delete deltree");

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
        if((chdir(param[1])==-1)){
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




int dohist(char* param[],tList Lista){
    if(param[1]!=NULL) {
        if (strcmp(param[1], "-c") == 0) {
            deleteList(Lista);

        } else {

            long n = strtol(param[1],NULL,10);
            tPosL p;
            int counter=0;
            char *cmd;
            for(p=Lista->next;p->next!=NULL;p=p->next){
                counter++;
            }
            p=Lista->next;

            if(n<=counter&&n>=1) {
                for (int i = 1; i <= n; i++) {


                    cmd = getChar(p, Lista);
                    printf("\n%s", cmd);
                    p = p->next;

                }

            }
            else{
                printf("Número de comando inexistente.\n");
            }


        }
    }else{
        printList(Lista);
    }
    return 1;
}

int docomando (char * param[], tList Lista,MemoryList Listamemoria, JobList Listajobs){
    if(param[1]!=NULL){
        long n= strtol(param[1],LNULL,10);
        tPosL p;
        int counter=0;
        char *cmd=param[1];
        char *trozos2[N/2];
        for(p=Lista->next;p->next!=NULL;p=p->next){
            counter++;
        }
        p=Lista->next;

        if(n<=counter&&n>=1) {
            for (int i = 1; i <= n; i++) {
                if(i==n){

                    strcpy(cmd,getChar(p, Lista));
                    TrocearCadena(cmd, trozos2);
                    ProcesarEntrada(trozos2,Lista,Listamemoria,Listajobs);
                    break;
                }
                p = p->next;

            }
        }else{
            printf("Número de comando inexistente.\n");
        }
    }else{
        printf("Tiene que introducir el número de comando que quiere ejecutar");
    }
    return 1;
}

int docreate (char *param[]){

    char path[1000];
    getcwd(path,sizeof (path));
    strcat(path,"/");
    if(param[1]!=NULL) {
        if (strcmp(param[1], "-f") == 0) {
            if (creat(strcat(path, param[2]), 0664) == -1) {
                perror("No se pudo crear el archivo");
            }
        } else {
            if (mkdir(strcat(path, param[1]), 0755) == -1) {
                perror("No se pudo crear el directorio");
            }
        }
    }else{
        docarpeta(param);
    }
    return 1;
}

int dostats (char *param[]){
    int i=1;
    int l=0;
    int link=0;
    int acc=0;
    struct stat st;
    if(param[1]!=NULL){
        while(param[i]!=NULL) {
            if (strcmp(param[i], "-long") == 0) {
                l=1;
            } else if (strcmp(param[i], "-link") == 0) {
                link=1;
            } else if (strcmp(param[i], "-acc") == 0) {
                acc=1;
            } else break;
            i++;
        }
        while(param[i]!=NULL){
            lstat(param[i],&st);
            if(lstat(param[i],&st)!=-1){
                int symb=0;
                if (l==1){
                    if(acc==1){
                        struct tm *acces=localtime(&st.st_atime);
                        printf("%02d/%02d/%02d-%02d:%02d ",acces->tm_year+1900,acces->tm_mon+1,acces->tm_mday,acces->tm_hour,acces->tm_min);
                    }else{
                        struct tm *mod=localtime(&st.st_mtime);
                        printf("%02d/%02d/%02d-%02d:%02d ",mod->tm_year+1900,mod->tm_mon+1,mod->tm_mday,mod->tm_hour,mod->tm_min);
                    }
                    if((link==1)&&('l'== LetraTF(st.st_mode))){
                        symb=1;
                    }
                    struct passwd *uid=getpwuid(st.st_uid);
                    struct group *gid=getgrgid(st.st_gid);
                    if(uid!=NULL){
                        printf("%lu (%ld) %s %s %s ", st.st_nlink, (long) st.st_ino, uid->pw_name, gid->gr_name,
                               ConvierteModo2(st.st_mode));
                    }else{
                        printf("%lu (%ld) %d %d %s ", st.st_nlink, (long) st.st_ino, st.st_uid, st.st_gid,
                               ConvierteModo2(st.st_mode));
                    }
                }
                if(symb==1){
                    printf("%ld %s->",st.st_size,param[i]);
                    char buf[PATH_MAX];
                    if(realpath(param[i],buf)!=NULL){
                        printf("%s\n",buf);
                    }else{
                        perror("No se pudo obtener la ruta");
                    }
                    i++;
                }else{
                    printf("%ld %s\n",st.st_size,param[i]);
                    i++;
                }
            }else{
                perror("No se pudo obtener los datos");
            }
        }
    }else{
        docarpeta(param);
    }
    return 1;
}

int dodelete(char *param[]){
    if(param[1]!=NULL){
        int i=1;
        while(param[i]!=NULL){
            if (remove(param[i]) == -1)
                perror("No se pudo borrar");
            i++;
        }
    }else{
        docarpeta(param);
    }
    return 1;

}

int dodeltree(char *param[]){
    int i=1;
    struct stat st;
    if(param[i]!=NULL){
        while(param[i]!=NULL) {
            lstat(param[i],&st);
            if('d'== LetraTF(st.st_mode)) {
                borrar_recursivo(param[i]);
            }
            else if (remove(param[i])==-1){
                perror("No se pudo borrar el fichero");
            }
            i++;
        }
    }else{
        docarpeta(param);
    }
    return 1;
}

int dolist(char *param[]){
    int i=1;
    int l=0;
    int link=0;
    int acc=0;
    int reca=0;
    int recb=0;
    int hid=0;
    if(param[1]!=NULL){
        while(param[i]!=NULL) {
            if (strcmp(param[i], "-long") == 0) {
                l=1;
            } else if (strcmp(param[i], "-link") == 0) {
                link=1;
            } else if (strcmp(param[i], "-acc") == 0) {
                acc=1;
            } else if (strcmp(param[i], "-reca") == 0) {
                reca=1;
            } else if (strcmp(param[i], "-recb") == 0) {
                recb=1;
            } else if (strcmp(param[i], "-hid") == 0) {
                hid=1;
            } else break;
            i++;
        }
        while (param[i]!=NULL) {
            if(reca==1||recb==1){
                procesardirectorioA(param[i],hid,l,acc,link,reca,recb);
            }else{
                ListarDirectorio(param[i],hid,l,acc,link);
            }
            i++;
        }
    }else{
        docarpeta(param);
    }
    return 1;
}

void borrar_recursivo(char *dir) {
    struct dirent *archivo;
    struct stat st;
    char aux[1000];
    DIR *d;
    if ((d=opendir(dir)) != NULL) {
        while ((archivo = readdir(d)) != NULL) {
            strcpy(aux, dir);
            strcat(strcat(aux, "/"), archivo->d_name);
            lstat(aux, &st);
            if (strcmp(archivo->d_name, ".") == 0 || strcmp(archivo->d_name, "..") == 0) continue;

            if ('d' == LetraTF(st.st_mode)) {
                borrar_recursivo(aux);

            }else if (remove(aux)==-1) {
                perror("No se pudo borrar el fichero");
            }

        }
        closedir(d);
        if  (rmdir(dir)==-1){
            perror("No se pudo borrar el directorio");
        }
    }else{
        perror("No se pudo abrir el directorio");
    }

}
void ListarDirectorio(char *dir,int hid,int l,int acc,int link) {
    struct dirent *archivo;
    struct stat st;
    char aux[1000];
    DIR *d;

    if ((d = opendir(dir)) != NULL) {
        printf("*********%s\n", dir);
        while ((archivo = readdir(d)) != NULL) {
            strcpy(aux, dir);
            strcat(strcat(aux, "/"), archivo->d_name);
            if(lstat(aux, &st)!=-1){
                if (hid == 1 || archivo->d_name[0] != '.') {
                    int symb = 0;
                    if (l == 1) {
                        if (acc == 1) {
                            struct tm *acces = localtime(&st.st_atime);
                            printf("%02d/%02d/%02d-%02d:%02d ", acces->tm_year + 1900, acces->tm_mon + 1, acces->tm_mday,
                                   acces->tm_hour, acces->tm_min);
                        } else {
                            struct tm *mod = localtime(&st.st_mtime);
                            printf("%02d/%02d/%02d-%02d:%02d ", mod->tm_year + 1900, mod->tm_mon + 1, mod->tm_mday, mod->tm_hour,
                                   mod->tm_min);
                        }
                        if ((link == 1) && ('l' == LetraTF(st.st_mode))) {
                            symb = 1;
                        }
                        struct passwd *uid = getpwuid(st.st_uid);
                        struct group *gid = getgrgid(st.st_gid);
                        if(uid!=NULL){
                            printf("%lu (%ld) %s %s %s ", st.st_nlink,st.st_ino, uid->pw_name, gid->gr_name,
                                   ConvierteModo2(st.st_mode));
                        }else{
                            printf("%lu (%ld) %d %d %s ", st.st_nlink, st.st_ino, st.st_uid, st.st_gid,
                                   ConvierteModo2(st.st_mode));
                        }
                    }
                    if (symb == 1) {
                        printf("%ld %s->", st.st_size, archivo->d_name);
                        char buf[PATH_MAX];
                        realpath(archivo->d_name, buf);
                        printf("%s\n", buf);
                    } else {
                        printf("%ld %s\n", st.st_size, archivo->d_name);
                    }
                }
            }else{
                perror("No se pudieron obtener los datos");
            }
        }
        closedir(d);
    }else{
        perror("No se pudo acceder al directorio");

    }
}

void procesardirectorioA(char *dir,int hid,int l,int acc,int link, int reca, int recb){
    struct stat st;
    struct dirent *archivo;
    char aux[1000];
    DIR *d;
    if(recb!=1) {
        ListarDirectorio(dir,hid,l,acc,link);
    }
    if ((d=opendir(dir)) != NULL) {
        while ((archivo = readdir(d)) != NULL) {
            strcpy(aux, dir);
            strcat(strcat(aux, "/"), archivo->d_name);
            lstat(aux, &st);
            if (strcmp(archivo->d_name, ".") == 0 || strcmp(archivo->d_name, "..") == 0) continue;

            if ('d' == LetraTF(st.st_mode)) {
                procesardirectorioA(aux,hid,l,acc,link,reca,recb);
            }
        }
        if(recb==1){
            ListarDirectorio(dir, hid, l, acc, link);
        }
        closedir(d);
    }
}


int doallocate(char *param[],MemoryList Listamemoria) {
    if(param[1]==NULL){
        char* cadena[]={"-tomasito","-blocks",};
        domemory(cadena,Listamemoria);
    }else{
        if(strcmp("-malloc",param[1])==0){
            if(param[2]!=NULL){
                long n= strtol(param[2],LNULL,10);
                do_AllocateMalloc(Listamemoria,n);
            }else{
                printf("***** Lista de bloques asignados malloc para el proceso %d\n",getpid());
                printListaMememoria(Listamemoria,MALLOC);
            }
        }else if (strcmp( "-mmap", param[1])==0){
            if(param[2]!=NULL){
                do_AllocateMmap(param,Listamemoria);
            }else{
                printf("***** Lista de bloques asignados malloc para el proceso %d\n",getpid());
                printListaMememoria(Listamemoria,MMAP);
            }

        }else if (strcmp( "-createshared", param[1])==0){
            if(param[2]!=NULL){
                do_AllocateCreateshared(param,Listamemoria);
            }else{
                printf("***** Lista de bloques asignados shared para el proceso %d\n",getpid());
                printListaMememoria(Listamemoria,SHARED);
            }
        }else if (strcmp( "-shared", param[1])==0){
            if(param[2]!=NULL){
                do_AllocateShared(param,Listamemoria);
            }else{
                printf("***** Lista de bloques asignados shared para el proceso %d\n",getpid());
                printListaMememoria(Listamemoria,SHARED);
            }
        }
    }
    return 1;
}


int dodeallocate(char *param[],MemoryList Listamemoria) {
    if(param[1]==NULL){
        char* cadena[]={"-tomasito","-blocks",};
        domemory(cadena,Listamemoria);
    }else{
        if(strcmp("-malloc",param[1])==0){
            if(param[2]!=NULL){
                long n= strtol(param[2],LNULL,10);
                pos p= EncontrarTamano(Listamemoria,n);
                if(p==NULL){
                    printf("No hay bloque de ese tamano asignado con malloc\n");
                }else{
                    free(p->address);
                    deleteAtPosition(p,Listamemoria);
                }
            }else{
                printf("***** Lista de bloques asignados malloc para el proceso %d\n",getpid());
                printListaMememoria(Listamemoria,MALLOC);
            }
        }else if((strcmp("-mmap",param[1]))==0){
            if(param[2]!=NULL){
                pos p = EncontrarFichero(Listamemoria, param[2]);
                if(p==NULL){
                    printf("***** Lista de bloques asignados mmap para el proceso %d\n",getpid());
                    printListaMememoria(Listamemoria,MMAP);
                }else{
                    close(p->id);
                    munmap(p->address,p->size);
                    deleteAtPosition(p, Listamemoria);
                }
            }else{
                printf("***** Lista de bloques asignados mmap para el proceso %d\n",getpid());
                printListaMememoria(Listamemoria,MMAP);
            }
        }else if((strcmp("-shared",param[1]))==0){
            if(param[2]!=NULL){
                long n= strtol(param[2],LNULL,10);
                int key=(int) n;
                pos p = EncontrarLlave(Listamemoria, key);
                if(p==NULL){
                    printf("No hay bloque de esa clave mapeado en el proceso\n");
                }else{
                    shmdt(p->address);
                    deleteAtPosition(p, Listamemoria);
                }
            }else{
                printf("***** Lista de bloques asignados shared para el proceso %d\n",getpid());
                printListaMememoria(Listamemoria,SHARED);
            }
        }else if((strcmp("-delkey",param[1]))==0){
            if(param[2]!=NULL){
                long n= strtol(param[2],LNULL,10);
                int key=(int) n;
                pos p = EncontrarLlave(Listamemoria, key);
                if(p==NULL){
                    printf("No hay bloque de esa clave mapeado en el proceso\n");
                }else{
                    do_DeallocateDelkey(param);
                }
            }else{
                printf("***** Lista de bloques asignados shared para el proceso %d\n",getpid());
                printListaMememoria(Listamemoria,SHARED);
            }

        }else{
            pos p= EncontrarPosicion(Listamemoria,param[1]);
            if(p==NULL){
                char* cadena[]={"-tomasito","-blocks",};
                domemory(cadena,Listamemoria);
            }else{
                if(p->tipo==1){
                    free(p->address);
                }else if(p->tipo==3){
                    close(p->id);
                    munmap(p->address,p->size);
                }else if(p->tipo==2){
                    shmdt(p->address);
                }
                deleteAtPosition(p,Listamemoria);
            }
        }
    }
    return 1;

}


int domemfill(char *param[]) {
    if(param[1]!=NULL){
        char* puntero;
        long tam;
        char letra;
        unsigned long adr= strtoul(param[1],&puntero,16);
        char* boom=(char *)adr;
        if(param[2]!=NULL){
            tam= strtol(param[2],NULL,10);
        }else{
            tam=128;
        }
        if(param[3]!=NULL){
            letra=param[3][0];
        }else{
            letra='A';
        }
        LlenarMemoria(boom,tam,letra);
        printf("Llenando %s bytes de memoria con el byte %c (%x) a partir de la direccion %s\n",param[2],letra,letra,param[1]);
    }
    return 1;

}


int domemdump(char *param[]) {
    if (param[1] != NULL) {
        char *puntero;
        long tam;
        unsigned long adr = strtoul(param[1], &puntero, 16);
        char *address = (char *) adr;
        if(param[2]!=NULL){
            tam = strtol(param[2], NULL, 10);
        }else{
            tam=25;
        }
        unsigned char *arr=(unsigned char *)address;
        printf("Volcando %lu bytes de memoria desde la direccion %s\n", tam, param[1]);
        size_t i, j;
        int linea=0;
        while (tam>0){
            int nb=(tam>=25)? 25:(int)tam;
            for (j=0; j < nb; j++) {
                if(arr[j+25*linea]!=0){
                    printf("%3c ", arr[j+25*linea]);
                } else {
                    printf(" ");
                }
            }
            printf("\n");
            for (i = 0; i < nb; i++) {
                printf(" %02x ",arr[i+25*linea]);
            }
            printf("\n");
            tam=tam-nb;
            linea++;
        }
    }
    return 1;

}

int pepe=0,jose=0,luis=0;
int domemory(char *param[],MemoryList listamemoria) {
    if(param[1]==NULL){
        char* cadena[]={"-tomasito","-all",};
        domemory(cadena,listamemoria);
    }else{
        if(strcmp("-blocks",param[1])==0){
            printf("Lista de bloques asignados a %d\n",getpid());
            printListaMememoria(listamemoria,MALLOC);
            printListaMememoria(listamemoria,MMAP);
            printListaMememoria(listamemoria,SHARED);
        }else if(strcmp("-vars",param[1])==0){
            int a=0,b=0,c=0;
            int static x=0,y=0,z=0;
            printf("Variables locales: \t %p,%p,%p\n",&a,&b,&c);
            printf("Variables estaticas: \t %p,%p,%p\n",&x,&y,&z);
            printf("Variables globales: \t %p,%p,%p\n",&pepe,&jose,&luis);
        }else if(strcmp("-funcs",param[1])==0){
            printf("Funciones programa\t %p,%p,%p\n",dofecha,docarpeta, doautores);
            printf("Funciones libreria\t %p,%p,%p\n", strtol, strcpy, printf);
        }else if(strcmp("-all",param[1])==0){
            char* cadena[]={"-pepito","-blocks"};
            domemory(cadena,listamemoria);
            char* cadena1[]={"-josito","-vars"};
            domemory(cadena1,listamemoria);
            char* cadena2[]={"-lusisto","-funcs"};
            domemory(cadena2,listamemoria);
        }else if(strcmp("-pmap",param[1])==0){
            Do_pmap();
        }
    }
    return 1;

}


int dorecurse(char *param[]) {
    if(param[1]!=NULL){
        long n = strtol(param[1], NULL, 10);
        int num=(int)n;
        Recursiva(num);
    }
    return 1;

}


int doinout(char *param[]) {
    if(strcmp("read",param[1])==0){
        do_I_O_read(param);
    }else if(strcmp("write",param[1])==0){
        do_I_O_write(param);
    }else{
        printf("uso: e-s [read][write] ......");
    }
    return 1;

}

void Recursiva (int n)
{
    char automatico[TAMANO];
    static char estatico[TAMANO];

    printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n,&n,automatico, estatico);

    if (n>0)
        Recursiva(n-1);
}


void LlenarMemoria (void *p, size_t cont, unsigned char byte)
{
    unsigned char *arr=(unsigned char *) p;
    size_t i;

    for (i=0; i<cont;i++)
        arr[i]=byte;
}

void * ObtenerMemoriaShmget (key_t clave, size_t tam,MemoryList Listamemoria)
{
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;
    time_t tiempoahora;
    time(&tiempoahora);
    if (tam)     /*tam distito de 0 indica crear */
        flags=flags | IPC_CREAT | IPC_EXCL;
    if (clave==IPC_PRIVATE)  /*no nos vale*/
    {errno=EINVAL; return NULL;}
    if ((id=shmget(clave, tam, flags))==-1)
        return (NULL);
    if ((p=shmat(id,NULL,0))==(void*) -1){
        aux=errno;
        if (tam)
            shmctl(id,IPC_RMID,NULL);
        errno=aux;
        return (NULL);
    }
    shmctl (id,IPC_STAT,&s);
    insertMemory(Listamemoria,SHARED,p,tiempoahora,(long)s.shm_segsz,0,NULL,clave);
    return (p);
}
void do_AllocateShared (char *tr[],MemoryList Listamemoria)
{
    key_t cl;
    size_t tam=0;
    void *p;
    if (tr[2]==NULL) {
        printListaMememoria(Listamemoria,2);
        return;
    }
    cl=(key_t)  strtoul(tr[2],NULL,10);
    if ((p=ObtenerMemoriaShmget(cl,tam,Listamemoria))!=NULL)
        printf ("Memoria compartida de clave %lu en %p\n",(unsigned long) cl, p);
    else
        printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
}


void do_AllocateCreateshared (char *tr[],MemoryList Listamemoria)
{
    key_t cl;
    size_t tam;
    void *p;
    if (tr[2]==NULL || tr[3]==NULL) {
        printListaMememoria(Listamemoria,2);
        return;
    }
    cl=(key_t)  strtoul(tr[2],NULL,10);
    tam=(size_t) strtoul(tr[3],NULL,10);
    if (tam==0) {
        printf ("No se asignan bloques de 0 bytes\n");
        return;
    }
    if ((p=ObtenerMemoriaShmget(cl,tam,Listamemoria))!=NULL)
        printf ("Asignados %lu bytes en %p\n",(unsigned long) tam, p);
    else
        printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
}


void * MapearFichero (char * fichero, int protection,MemoryList Listamemoria)
{
    int df, map=MAP_PRIVATE,modo=O_RDONLY;
    struct stat s;
    void *p;
    if (protection&PROT_WRITE)
        modo=O_RDWR;
    if (stat(fichero,&s)==-1 || (df=open(fichero, modo))==-1)
        return NULL;
    if ((p=mmap (NULL,s.st_size, protection,map,df,0))==MAP_FAILED)
        return NULL;
    time_t tiempoahora;
    time(&tiempoahora);
    insertMemory(Listamemoria,MMAP,p, tiempoahora,s.st_size,df,fichero,0);
    return p;
}

void do_AllocateMmap(char *arg[],MemoryList listamemoria)
{
    char *perm;
    void *p;
    int protection=0;
    if (arg[2]==NULL)
    {printListaMememoria(listamemoria, 2);
        return;}
    if ((perm=arg[3])!=NULL && strlen(perm)<4) {
        if (strchr(perm,'r')!=NULL) protection|=PROT_READ;
        if (strchr(perm,'w')!=NULL) protection|=PROT_WRITE;
        if (strchr(perm,'x')!=NULL) protection|=PROT_EXEC;
    }
    if ((p=MapearFichero(arg[2], protection, listamemoria)) == NULL)
        perror ("Imposible mapear fichero");
    else
        printf ("fichero %s mapeado en %p\n", arg[2], p);
}


void do_DeallocateDelkey (char *args[])
{
    key_t clave;
    int id;
    char *key=args[2];

    if (key==NULL || (clave=(key_t) strtoul(key,NULL,10))==IPC_PRIVATE){
        printf ("      delkey necesita clave_valida\n");
        return;
    }
    if ((id=shmget(clave,0,0666))==-1){
        perror ("shmget: imposible obtener memoria compartida");
        return;
    }
    if (shmctl(id,IPC_RMID,NULL)==-1)
        perror ("shmctl: imposible eliminar memoria compartida\n");
}



ssize_t LeerFichero (char *f, void *p, size_t cont)
{
    struct stat s;
    ssize_t  n;
    int df,aux;

    if (stat (f,&s)==-1 || (df=open(f,O_RDONLY))==-1)
        return -1;
    if (cont==-1)   /* si pasamos -1 como bytes a leer lo leemos entero*/
        cont=s.st_size;
    if ((n=read(df,p,cont))==-1){
        aux=errno;
        close(df);
        errno=aux;
        return -1;
    }
    close (df);
    return n;
}

void do_I_O_read (char *ar[])
{
    size_t cont=-1;
    char* puntero;
    ssize_t n;
    if (ar[2]==NULL || ar[3]==NULL){
        printf ("faltan parametros\n");
        return;
    }
    unsigned long adr= strtoul(ar[3],&puntero,16);
    char* p=(char *)adr;  //convertimos de cadena a puntero
    if (ar[4]!=NULL)
        cont=(size_t) atoll(ar[4]);
    if ((n=LeerFichero(ar[2],p,cont))==-1)
        perror ("Imposible leer fichero");
    else
        printf ("leidos %lld bytes de %s en %p\n",(long long) n,ar[2],p);
}
void do_I_O_write (char *ar[])
{
    size_t cont=-1;
    char* puntero;
    int o=0;
    ssize_t n;
    if(strcmp(ar[2],"-o")==0){
        o=1;
    }
    if (ar[3+o]==NULL || ar[2+o]==NULL){
        printf ("faltan parametros\n");
        return;
    }
    unsigned long adr= strtoul(ar[3+o],&puntero,16);
    char* p=(char *)adr;  //convertimos de cadena a puntero
    if (ar[4+o]!=NULL)
        cont=(size_t) atoll(ar[4+o]);
    if ((n=EscribirFichero(ar[2+o],p,cont,o))==-1)
        perror ("Imposible leer fichero");
    else
        printf ("escritos %lld bytes en %s desde %p\n",(long long) n,ar[2+o],p);
}

ssize_t EscribirFichero (char *f, void *p, size_t cont,int overwrite)
{
    ssize_t  n;
    int df,aux, flags=O_CREAT | O_EXCL | O_WRONLY;

    if (overwrite)
        flags=O_CREAT | O_WRONLY | O_TRUNC;

    if ((df=open(f,flags,0777))==-1)
        return -1;

    if ((n=write(df,p,cont))==-1){
        aux=errno;
        close(df);
        errno=aux;
        return -1;
    }
    close (df);
    return n;
}



void Do_pmap (void) /*sin argumentos*/
{ pid_t pid;       /*hace el pmap (o equivalente) del proceso actual*/
    char elpid[32];
    char *argv[4]={"pmap",elpid,NULL};

    sprintf (elpid,"%d", (int) getpid());
    if ((pid=fork())==-1){
        perror ("Imposible crear proceso");
        return;
    }
    if (pid==0){
        if (execvp(argv[0],argv)==-1)
            perror("cannot execute pmap (linux, solaris)");

        argv[0]="procstat"; argv[1]="vm"; argv[2]=elpid; argv[3]=NULL;
        if (execvp(argv[0],argv)==-1)/*No hay pmap, probamos procstat FreeBSD */
            perror("cannot execute procstat (FreeBSD)");

        argv[0]="procmap",argv[1]=elpid;argv[2]=NULL;
        if (execvp(argv[0],argv)==-1)  /*probamos procmap OpenBSD*/
            perror("cannot execute procmap (OpenBSD)");

        argv[0]="vmmap"; argv[1]="-interleave"; argv[2]=elpid;argv[3]=NULL;
        if (execvp(argv[0],argv)==-1) /*probamos vmmap Mac-OS*/
            perror("cannot execute vmmap (Mac-OS)");
        exit(1);
    }
    waitpid (pid,NULL,0);
}

void do_AllocateMalloc(MemoryList listaMemoria,long tamano){
    char* p = malloc(tamano);
    time_t tiempoahora;
    time(&tiempoahora);
    insertMemory(listaMemoria,MALLOC,p,tiempoahora,tamano,0,NULL,0);
    printf("Asignados %ld en %s\n",tamano, ptr2string(p));
}


void printListaMememoria(MemoryList L, int tipo){
    pos p;
    for (p = L->next; p!= NULL; p = p->next){
        if(tipo == 1&&tipo==p->tipo) {
            char* addr= ptr2string(p->address);
            struct tm *ctime = localtime(&p->time);
            printf("\t%s%12ld %d %d %02d:%02d malloc\n", addr, p->size, ctime->tm_mon+1,ctime->tm_mday,ctime->tm_hour, ctime->tm_min);
        }
        if(tipo == 3 && tipo== p->tipo) {
            char* addr= ptr2string(p->address);
            struct tm *ctime = localtime(&p->time);
            printf("\t%s%12ld %d %d %02d:%02d mmap %s (descriptor:%d)\n", addr, p->size, ctime->tm_mon+1,ctime->tm_mday,ctime->tm_hour, ctime->tm_min, p->fich, p->id);
        }
        if(tipo == 2&& tipo== p->tipo) {
            char* addr= ptr2string(p->address);
            struct tm *ctime = localtime(&p->time);
            printf("\t%s%12ld %d %d %02d:%02d shared (key:%d)\n", addr, p->size, ctime->tm_mon+1,ctime->tm_mday,ctime->tm_hour, ctime->tm_min, p->key);
        }
    }
}


int dopriority ( char *param[]){
    if ( param[1]!=NULL) {
        unsigned long p= strtoul(param[1], NULL, 10);
        if (param[2] != NULL){
            int prio= atoi(param[2]);
            setpriority(PRIO_PROCESS, p,(int)prio);
            printf("Prioridad del proceso %lu es %d\n" ,p, prio);
        }else{
            printf("Prioridad del proceso %lu es %d\n" ,p, getpriority(PRIO_PROCESS, p));
        }
    }else{
        printf("Prioridad del proceso %d es %d\n", getpid(), getpriority(PRIO_PROCESS, getpid()) );
    }
    return 1;
}

int dofork (char *param[]){
    int pid;
    if ((pid=fork())==-1){
        perror ("Imposible crear proceso\n");
    }else if (pid ==0){
        printf("Ejecutando proceso %d\n", getpid());
    }else{
        waitpid(pid, NULL, 0);
    }
    return 1;
}


extern char ** environ;


int doshowenv(char *param[]){
    if(param[1]==NULL){
        MuestraEntorno(puntero,"main arg3");
    }else{
        if(strcmp(param[1],"-addr")==0){
            printf("environ: %p (almacenado en %p)\n",&environ[0],&environ);
            printf("main arg3: %p (almacenado en %p)\n",&environ[0],&puntero);
        }else if(strcmp(param[1],"-environ")==0){
            MuestraEntorno(environ,"environ");
        }
    }
    return 1;
}

int doshowvar ( char *param[]){
    if(param[1]==NULL){
        MuestraEntorno(puntero,"main arg3");
    }else{
        int pos;
        if((pos=BuscarVariable(param[1],environ))==-1){
            perror("No esta en la lista de variables");
        }else{
            printf("Con arg3 main %s (%p) %p\n",puntero[pos],puntero[pos],&puntero[pos]);
            printf("Con environ %s (%p) %p\n",environ[pos],environ[pos],environ[pos]);
            printf("Con getenv %s %p\n",getenv(param[1]),getenv(param[1]));
        }
    }
    return 1;
}

void MuestraEntorno ( char *entorno[], char *nombre_variable){
    for( int i = 0; entorno[i]!=NULL; i++){
        printf("%p->%s [%d]=(%p) %s \n", &entorno[i], nombre_variable, i, entorno[i], entorno[i]);
    }
}


int dochangevar(char *param[]){
    if (param[1] != NULL) {

        if (strcmp(param[1], "-a") == 0) {
            CambiarVariable(param[2],param[3],puntero);
        }
        else if (strcmp(param[1], "-e") == 0) {
            CambiarVariable(param[2],param[3],environ);
        } else if (strcmp(param[1], "-p") == 0) {
            char aux[TAMANO];
            strcpy(aux,param[2]);
            strcat(aux,"=");
            strcat(aux,(param[3]));
            putenv(aux);
        }else {
            MuestraEntorno(puntero,"main arg3");
        }
    }
    return 1;
}

char * Nombre(uid_t u)
{
    struct passwd *p=getpwuid(u);

    if (p!=NULL)
        return p->pw_name;
    return "???????";
}


int dolistjobs (char *param[], JobList L){
    posJ p;
    char statuschar[TAMANO];
    for (p = L->next; p != NULL; p = p->next) {
        tipostatus(p);

        struct tm *ctime = localtime(&p->time);
        if (strcmp(p->status,"TERMINADO")==0)  {
            printf("%d %12s p=%d %d/%02d/%02d %02d:%02d:%02d %s (%03d) %s\n", p->pid, Nombre(p->uid),
                   getpriority(PRIO_PROCESS, p->pid), ctime->tm_year+1900,ctime->tm_mon+1,ctime->tm_mday,ctime->tm_hour,ctime->tm_min,ctime->tm_sec, p->status, p->returnstatus, p->lineacomando);
        }
        else if((strcmp(p->status,"SEÑALADO")==0) )
        {
            strcpy(statuschar,NombreSenal(p->returnstatus));

            printf("%d %12s p=%d %d/%02d/%02d %02d:%02d:%02d %s (%s) %s\n", p->pid, Nombre(p->uid),
                   getpriority(PRIO_PROCESS, p->pid), ctime->tm_year+1900,ctime->tm_mon+1,ctime->tm_mday,ctime->tm_hour,ctime->tm_min,ctime->tm_sec, p->status, statuschar, p->lineacomando);
        }
        else if (strcmp(p->status,"ACTIVO")==0 || (strcmp(p->status,"STOPPED")==0))  {

            printf("%d %12s p=%d %d/%02d/%02d %02d:%02d:%02d %s (%03d) %s\n", p->pid, Nombre(p->uid),
                   getpriority(PRIO_PROCESS, p->pid), ctime->tm_year+1900,ctime->tm_mon+1,ctime->tm_mday,ctime->tm_hour,ctime->tm_min,ctime->tm_sec, p->status, p->returnstatus, p->lineacomando);
        }
    }
    return 1;
}

void tipostatus (posJ p){
    if (waitpid(p->pid,&p->returnstatus, WNOHANG |WUNTRACED |WCONTINUED) == p->pid){
        if(WIFEXITED(p->returnstatus)){
            p->status= "TERMINADO";
            p->returnstatus = WEXITSTATUS(p->returnstatus);
        }else if(WIFSIGNALED(p->returnstatus)){
            p->status= "SEÑALADO";
            p->returnstatus = WTERMSIG(p->returnstatus);
        }else if(WIFSTOPPED(p->returnstatus)){
            p->status= "STOPPED";
            p->returnstatus = WSTOPSIG(p->returnstatus);
        }else if(WIFCONTINUED(p->returnstatus)) {
            p->status= "ACTIVO";
            p->returnstatus = 0;   //fariña cambio
        }
    }
}

int doexecute(char* param[],JobList L){
    int j;
    int i=1;
    char* arg[TAMANO];
    arg[0]=NULL;
    while((j= BuscarVariable(param[i],environ))!=-1){
        arg[i]=environ[j];
        i++;
    }
    arg[i]=NULL;
    char *ejecutable=param[i];
    char *opt[TAMANO];
    j=0;
    opt[0]=NULL;

    while(param[i]!=NULL && param[i][0]!='&' && param[i][0]!='@'){
        opt[j]=param[i];
        i++;
        j++;
    }
    opt[j]=NULL;

    int prio=0,prioridad=0;
    if(param[i]!=NULL && param[i][0]=='@'){
        prio=1;
        prioridad= atoi(param[i]+1);
    }
    if(prio==1)
        setpriority(PRIO_PROCESS, getpid(),prioridad);

    if(arg[0]!=NULL){
        if(OurExecvpe(ejecutable,opt,arg)==-1)
            perror("No se puede ejecutar el comando");
    }else{
        if(OurExecvpe(ejecutable,opt,environ)==-1)
            perror("No se puede ejecutar el comando");
    }
    return 1;
}

char * Ejecutable (char *s)
{
    char path[TAMANO];
    static char aux2[TAMANO];
    struct stat st;
    char *p;
    if (s==NULL || (p=getenv("PATH"))==NULL)
        return s;
    if (s[0]=='/' || !strncmp (s,"./",2) || !strncmp (s,"../",3))
        return s;
    strncpy (path, p, TAMANO);
    for (p=strtok(path,":"); p!=NULL; p=strtok(NULL,":")){
        sprintf (aux2,"%s/%s",p,s);
        if (lstat(aux2,&st)!=-1)
            return aux2;
    }
    return s;
}

int OurExecvpe(char *file, char *const argv[], char *const envp[])
{
    return (execve(Ejecutable(file),argv, envp));
}

int puntos(char *param[],JobList L){
    int j;
    int i=0;
    int pid, pid2;
    char* arg[TAMANO];
    arg[0] = NULL;

    while((j= BuscarVariable(param[i],environ))!=-1){
        arg[i]=environ[j];
        i++;
    }
    arg[i]=NULL;

    char *ejecutable=param[i];
    char *opt[TAMANO];
    opt[0]=NULL;
    j=0;
    while(param[i]!=NULL && param[i][0]!='&' && param[i][0]!='@'){
        opt[j]=param[i];
        i++;
        j++;
    }
    opt[j]=NULL;

    int prio=0,back=0,prioridad=0;
    if(param[i]!=NULL && param[i][0]=='@'){
        prio=1;
        prioridad= atoi(param[i]+1);
        i++;
    }

    if(param[i]!=NULL && param[i][0]=='&'){
        back=1;
    }
    pid=fork();
    pid2=getpid();
    if(back==1){
        if(pid==0){
            if(prio==1)
                setpriority(PRIO_PROCESS, pid2,prioridad);
            printf("%d", getpriority(PRIO_PROCESS,pid2));
            if(arg[0]!=NULL){
                if(OurExecvpe(ejecutable,opt,arg)==-1)
                    perror("No se puede ejecutar el comando");
                exit(1);
            }else{
                if(OurExecvpe(ejecutable,opt,environ)==-1)
                    perror("No se puede ejecutar el comando");
                exit(1);
            }
        }else{
            time_t tiempoahora;
            time(&tiempoahora);
            char lineacomando[TAMANO];
            strcpy(lineacomando,ejecutable);
            i=1;
            while(opt[i]!=NULL){
                char *boom=opt[i];
                strcat(lineacomando," ");
                strcat(lineacomando,boom);
                i++;
            }
            uid_t uid = getuid();
            insertJobList(L, pid, "ACTIVO", getpriority(PRIO_PROCESS,pid), lineacomando, tiempoahora,
                          uid);
        }
    }else{
        if(pid==0){
            if(prio==1)
                setpriority(PRIO_PROCESS, pid2,(int)prioridad);
            printf("%d", getpriority(PRIO_PROCESS,pid2));
            if(arg[0]!=NULL){
                if(OurExecvpe(ejecutable,opt,arg)==-1)
                    perror("No se puede ejecutar el comando");
                exit(1);
            }else{
                if(OurExecvpe(ejecutable,opt,environ)==-1)
                    perror("No se puede ejecutar el comando");
                exit(1);
            }
        }else{
            waitpid(pid,NULL,0);
        }
    }
    return 1;
}/*
void Cmd_fork (char *tr[])
{
	pid_t pid;
	if ((pid=fork())==0){
		printf ("ejecutando proceso %d\n", getpid());
	}
	else if (pid!=-1)
		waitpid (pid,NULL,0);
}
 */
int deljobs (char *param[], JobList L){
    if (param[1]!=NULL){
        int i=1;
        int term=0;
        int sig=0;
        while(param[i]!=NULL) {
            //    if (strcmp(param[1], "-term") == 0) {                 //cambio fariña
            //        term=1;                                           //cambio fariña
            //    } else if (strcmp(param[1], "-sig") == 0) {           //cambio fariña
            //        sig=1;                                            //cambio fariña

            if (strcmp(param[i], "-term") == 0) {
                term=1;
            } else if (strcmp(param[i], "-sig") == 0) {
                sig=1;


            } else break;
            i++;
        }
        posJ p;
        for (p = L->next; p != NULL; p = p->next) {
            tipostatus(p);
            if (strcmp (p->status , "TERMINADO")==0 && term == 1){            // fariña: uninitilized (se un proceso aínda está activo)
                deleteAtJPosition(p, L);
            }
            else if ( strcmp (p->status, "SEÑALADO")==0 && sig == 1){
                deleteAtJPosition(p, L);
            }
        }

    }else{
        dolistjobs(param, L);
    }
    return 1;

}
int CambiarVariable(char * var, char * valor, char *e[]) {
    int pos;
    char *aux;

    if ((pos=BuscarVariable(var,e))==-1)
        return(-1);

    if ((aux=(char *)malloc(strlen(var)+strlen(valor)+2))==NULL)
        return -1;
    strcpy(aux,var);
    strcat(aux,"=");
    strcat(aux,valor);
    e[pos]=aux;
    return (pos);
}
int BuscarVariable (char * var, char *e[])  /*busca una variable en el entorno que se le pasa como parámetro*/
{
    int pos=0;
    char aux[TAMANO];

    strcpy (aux,var);
    strcat (aux,"=");

    while (e[pos]!=NULL)
        if (!strncmp(e[pos],aux,strlen(aux)))
            return (pos);
        else
            pos++;
    errno=ENOENT;   /*no hay tal variable*/
    return(-1);
}

int job ( char * param[], JobList L){
    posJ  p;
    if (param[1]!=NULL) {
        for (p = L->next; p != NULL; p = p->next) {
            if (strcmp((param[1]), "-fg")== 0){
                if (p->pid== strtol(param[2], NULL, 10)) {
                    //fariña, ojo ao seguinte... NON RECOLLEDES o estado no que rematou o proceso !!!!
                    // se o mato cunha señal --> vós dicides que morreu normalmente !!!
                    if (strcmp(p->status, "ACTIVO") == 0) {
                        if(p->returnstatus==0){
                            waitpid(p->pid,NULL,0);
                            tipostatus(p);
                        printf("Proceso %d terminado normalmente. Valor devuelto %d\n", p->pid, p->returnstatus);
                    }else{
                            printf("Proceso %d terminado con la señal %s\n", p->pid, NombreSenal(p->returnstatus));
                        }
                        deleteAtJPosition(p, L);
                    } else {
                        printf("Proceso %d ya está finalizado\n", p->pid);
                        deleteAtJPosition(p, L);
                        break;
                    }
                }
            }else{
                if ( p->pid == strtol(param[1], NULL, 10)){
                    tipostatus(p);
                    struct tm *ctime = localtime(&p->time);
                    printf("%d %12s p=%d %d/%02d/%02d %02d:%02d:%02d %s (%03d) %s\n",p->pid, Nombre(p->uid),
                           getpriority(PRIO_PROCESS, p->pid), ctime->tm_year+1900,ctime->tm_mon+1,ctime->tm_mday,ctime->tm_hour,ctime->tm_min,ctime->tm_sec, p->status, p->returnstatus, p->lineacomando);
                }
            }
        }
    }else{
        dolistjobs(param, L);
    }
    return 1;
}
