#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#define POSIX_C_SOURCE 200809L

int read_N_ieme (int n, int fd){
    int entier;
    off_t position;
    position = lseek(fd,n*sizeof(int),SEEK_SET);
    if (position==-1){
        perror("lseekread");
        exit(1);
    }
    if(read(fd,&entier,sizeof(int))==-1){
        perror("read");
        exit(2);
    }
    return entier;
}

void write_N_ieme (int n, int entier, int fd){
    
    off_t position;
    position = lseek(fd,n*sizeof(int),SEEK_SET);
    if (position==-1){
        perror("lseekwrite");
        exit(3);
    }
    if(write(fd,&entier,sizeof(int))==-1){
        perror("write");
        exit(4);
    }
}

int main (int argc,char *argv[]){

    if (argc < 3 || argc > 4) {
        fprintf(stderr, "Usage: %s <n> [<entier>] <fichier>\n", argv[0]);
        exit(5);
    }

    if (argc==3) {   // Lecture seulement
        int n = atoi(argv[1]);
        int fich = open(argv[2], O_RDONLY);
        if (fich == -1) {
            perror("openREADONLY");
            exit(6);
        }
        read_N_ieme(n,fich);
    } else { // (if argc==4) Ecriture seulement  
        int n = atoi(argv[1]);
        int entier = atoi(argv[2]);
        int fich = open(argv[3],O_WRONLY | O_CREAT | S_IRUSR | S_IWUSR | S_IRGRP);
        if (fich == -1) {
            perror("openWRITEONLY");
            exit(7);
        }
        write_N_ieme(n, entier, fich);
    }

    return 0;
}