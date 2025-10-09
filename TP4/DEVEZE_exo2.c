#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#define N 10
#define MAX_BASSIN 5
#define POSIX_C_SOURCE 200809L 


int main () {
    int Remplir[2];
    int Etat[2];
    int entier1 = 1;
    int entierm1 = -1;
    int nblus, value;
    int bassin;
    int infofils;
    int f_flags;

    if(pipe(Remplir)==-1){
        perror("Echec creation pipe Remplir");
        exit(2);
    }
    if(pipe(Etat)==-1){
        perror("Echec creation pipe Etat");
        exit(3);
    }


    switch(fork()){
        case -1: 
        perror("Echec creation fils");
        exit(4);
        
        case 0: /* Contexte du fils */
        close(Remplir[1]);
        close(Etat[0]);
       
        while((nblus=read(Remplir[0],(void*)&value,sizeof(int)))>0){
            if(value>0){
                bassin+=value;
                printf("*");
                fflush(stdout);
            if(bassin>=MAX_BASSIN){
                if(write(Etat[1],(void*)&bassin,sizeof(int))==-1) {
                    perror("Echec write du fils dans le tube Etat");
                    exit(8);
                }
            }
        }
        else{
            bassin=0;
            printf("\n");
            fflush(stdout);
        }
        }
        close(Remplir[0]);
        close(Etat[1]);
        exit(1);


        default: /* Contexte du père */
        close(Remplir[0]);
        close(Etat[1]);

        
        /* mode non bloquant pour le tube Etat dans le Père */
        f_flags = fcntl(Etat[0], F_GETFL); /* Récupération des flags */
        f_flags |= O_NONBLOCK; /* Positionnement du flag de non blocage */
        fcntl(Etat[0], F_SETFL, f_flags); /* Mis à jour des flags */

        for(int i=0;i<N;i++){
            sleep(1);
            if(write(Remplir[1],(void*)&entier1,sizeof(entier1))==-1){
                perror("Echec write du père dans le tube Remplir");
                exit(5);
            }


            if((nblus=read(Etat[0],(void*)&value,sizeof(value)))>0){
                if(write(Remplir[1],(void*)&entierm1,sizeof(entierm1))==-1){
                    perror("Echec write du père dans le tube Remplir");
                    exit(6);
                }
            }

        }
        if(nblus==-1){
            perror("echec read pere dans le tube Etat");
            exit(7);
        }
        close(Remplir[1]);
        close(Etat[0]);
        wait(&infofils);
        printf("\n");
        printf("[Père] : Mon fils %d est terminé avec le code de retour : %d\n",getpid(),WEXITSTATUS(infofils));
        exit(0);
    }

     return 0;
}