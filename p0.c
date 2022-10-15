#include "headed_linked_list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/syscall.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <limits.h>

#define N 48

void leerEntrada(char *cadena);
int TrocearCadena(char *cadena, char *trozos[]);
int ProcesarEntrada(char *trozos[],tList Lista);
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
int doayuda(char *param[]);
int dostats(char *param[]);
int dolist(char *param[]);
int dodelete(char *param[]);
int dodeltree(char *param[]);
int docreate(char *param[]);
int docomando (char *param[], tList Lista);


int main(){
    int acabar=0;
    char cadena[N] ;
    char *trozos[N/2];
    tList Lista;
    createList(&Lista);


    while ( acabar!=-1 ){

        imprimirPrompt();

        leerEntrada(cadena);
        insertItem(cadena,Lista);
        TrocearCadena(cadena, trozos);
        acabar=ProcesarEntrada(trozos,Lista);

    }


    free (Lista);
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

int ProcesarEntrada(char * trozos[],tList Lista){
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
        i=docomando(param,Lista);
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



    }else {
        printf("\nEste comando no existe\n");
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

char * infoparametros(char * cmd){

    struct t_ayuda{
        char* cmd;
        char* msg;
    };
    static struct t_ayuda V[16];

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



    int i;
    for (i=0; i<16; i++)
        if (strcmp(V[i].cmd, cmd) ==0)
            return V[i].msg;
    if(i==16)
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

int docomando (char * param[], tList Lista){
    if(param[1]!=NULL){
        long n= strtol(param[1],LNULL,10);
        tPosL p;
        int counter=0;
        char *cmd;
        char *trozos2[N/2];
        for(p=Lista->next;p->next!=NULL;p=p->next){
            counter++;
        }
        p=Lista->next;

        if(n<=counter&&n>=1) {
            for (int i = 1; i <= n; i++) {
                if(i==n){

                    cmd = getChar(p, Lista);
                    TrocearCadena(cmd, trozos2);
                    ProcesarEntrada(trozos2,Lista);
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
    if(param[1]!=NULL){
        if(strcmp(param[1], "-f")==0){
            if(creat(strcat(path,param[2]),0664)==-1){
                perror("No se pudo crear el archivo");
            }
        }else{
            if(mkdir(strcat(path,param[1]),0755)==-1){
                perror("No se pudo crear el directorio");
            }
        }
    }else{
        printf("%s",path);
    }
    return 1;
}

int dostats (char *param[]){
    int i=1;
    int l=0;
    int link=0;
    int acc=0;
    int symb=0;
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
                if (l==1){
                    if(acc==1){
                        struct tm *acces=localtime(&st.st_atime);
                        printf("%d/%d/%d-%d:%d ",acces->tm_year+1900,acces->tm_mon+1,acces->tm_mday,acces->tm_hour,acces->tm_min);
                    }else{
                        struct tm *mod=localtime(&st.st_mtime);
                        printf("%d/%d/%d-%d:%d ",mod->tm_year+1900,mod->tm_mon+1,mod->tm_mday,mod->tm_hour,mod->tm_min);
                    }
                    if((link==1)&&('l'== LetraTF(st.st_mode))){
                            symb=1;
                        }
                    struct passwd *uid=getpwuid(st.st_uid);
                    struct group *gid=getgrgid(st.st_gid);
                    printf("%lu (%ld) %s %s %s ",st.st_nlink,(long)st.st_ino,uid->pw_name,gid->gr_name,ConvierteModo2(st.st_mode));
                }
                if(symb==1){
                printf("%ld %s->",st.st_size,param[i]);
                    char buf[PATH_MAX];
                    char *symbolic=realpath(param[i],buf);
                    int j;
                    char *trozo=strtok(symbolic,"/");
                    char* ultimo;
                        while(trozo!=NULL){
                            ultimo=trozo;
                            trozo= strtok(NULL,"/");
                            j++;
                        }
                printf("%s\n",ultimo);
                i++;
                }else{
                    printf("%ld %s\n",st.st_size,param[i]);
                    i++;
                }
            }else{
                perror("No se pudo obtener los datos de ese archivo");
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
                perror("No se pudo borrar el archivo");
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
                perror("ERROR");
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
    struct dirent *d;
    DIR  *dir;
    struct stat st;
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
        if (param[i]!=NULL) {
            dir = opendir(param[i]);
            if (dir != NULL) {

                printf("*********%s\n", param[i]);
                while ((d = readdir(dir)) != NULL) {
                    lstat(param[i], &st);
                    if (lstat(param[i], &st) != -1) {

                                if (l == 1) {
                                    if (acc == 1) {
                                        struct tm *acces = localtime(&st.st_atime);
                                        printf("%d/%d/%d-%d:%d ", acces->tm_year + 1900, acces->tm_mon + 1,
                                               acces->tm_mday,
                                               acces->tm_hour, acces->tm_min);
                                    } else {
                                        struct tm *mod = localtime(&st.st_mtime);
                                        printf("%d/%d/%d-%d:%d ", mod->tm_year + 1900, mod->tm_mon + 1, mod->tm_mday,
                                               mod->tm_hour,
                                               mod->tm_min);
                                    }
                                    if (link == 1) {
                                        char a = LetraTF(st.st_mode);
                                        char *type = &a;
                                        if (strcmp(type, "l") == 0) {
                                            link = st.st_rdev;
                                        }
                                    }
                                    printf("%d", link);
                                    struct passwd *uid = getpwuid(st.st_uid);
                                    struct group *gid = getgrgid(st.st_gid);
                                    printf("(%ld), %s %s %s ", (long) st.st_ino, uid->pw_name, gid->gr_name,
                                           ConvierteModo2(st.st_mode));
                                }if (hid == 1) {
                            printf("%ld %s\n", st.st_size, d->d_name);


                        } else {
                            if (strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0) {

                                printf("%ld %s\n", st.st_size, d->d_name);
                                i++;
                            }
                        }

                    }
                }

                closedir(dir);
            }else {
                perror ("Este directorio no existe\n");
            }
        }else {
            perror("No se puedo abrir el directorio\n");
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
    lstat(dir, &st);

    if ((d=opendir(dir)) != NULL) {
        while ((archivo = readdir(d)) != NULL) {
            strcpy(aux, dir);
            strcat(strcat(aux, "/"), archivo->d_name);

            if (strcmp(archivo->d_name, ".") == 0 || strcmp(archivo->d_name, "..") == 0) continue;

            if ('d' == LetraTF(st.st_mode)) {
                borrar_recursivo(aux);

            }

            if (remove(aux)) {
            }
        }
        closedir(d);
    }


}


