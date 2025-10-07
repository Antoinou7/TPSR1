#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define POSIX_C_SOURCE 200809L 



int main() {
int tube[2];
int n=4;
int infofils;
if(pipe(tube)==-1){
    perror("Echec creation pipe"); 
    exit(2);
}

switch(fork()) {
    case -1:
    perror("Echec creation fils");
    exit(3);
    case 0 : /* Contexte du fils*/
    close(tube[1]); /* Le fils n'ecrit pas dans le tube, le fils est consommateur */
    int nblus;
    while(read(tube[0],(void*)&nblus,sizeof(nblus))>0){
        printf("[Fils] %d\n",nblus);
    }
    exit(1);


    default: /* Contexte du pere */
    
    close(tube[0]); /* Le père ne lit pas dans le tube, le père est producteur */
    for(int i=1;i<=n;i++){
        sleep(1);
        if(write(tube[1],(void*)&i,sizeof(i))==-1){
            perror("Echec write du père dans le tube");
            exit(4);
        }
    }
    close(tube[1]); /* Très important : on ferme l'écriture du tube */
    wait(&infofils);
    printf("[Père] : Mon fils %d est terminé avec le code de retour : %d\n",getpid(),WEXITSTATUS(infofils));
    exit(0);
}


}