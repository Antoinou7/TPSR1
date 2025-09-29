#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void Affiche_inode(struct stat* Infos){
    char* type = S_ISREG(Infos->st_mode) ? "fichier ordinaire" :
                  S_ISDIR(Infos->st_mode) ? "répertoire" :
                  S_ISCHR(Infos->st_mode) ? "fichier spécial de caractère" :
                  S_ISBLK(Infos->st_mode) ? "fichier spécial de bloc" :
                  S_ISFIFO(Infos->st_mode) ? "FIFO" :
                  S_ISLNK(Infos->st_mode) ? "lien symbolique" :
                  S_ISSOCK(Infos->st_mode) ? "socket" : "inconnu";


    printf("Numéro d'inode : %ld, le type est : %s, la taille du %s en octets est de %ld et la date de dernière modification est : %s\n",Infos->st_ino, type, type, Infos->st_size, ctime(&(Infos->st_mtime)));
}



int main(int argc, char* argv[]) {

    if(argc!=2) {
        fprintf(stderr,"Usage : %s fich\n",argv[0]);
        exit(1);
    }


    struct stat Infos;
  if(lstat(argv[1],&Infos)!=0) {
    perror("lstat");
    exit(2);
  }
  printf("Désignation du fichier : %s\n",argv[1]);
  Affiche_inode(&Infos);


return 0;
}