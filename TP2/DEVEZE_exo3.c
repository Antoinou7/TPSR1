#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#define POSIX_C_SOURCE 200809L
#define TAILLE_BLOC 512

void readbase(char nom_fich[]) {
     int src = open(nom_fich, O_RDONLY);
   
   
    if (src == -1) {
        perror(nom_fich);
        exit(EXIT_FAILURE);
    }

    char buffer[TAILLE_BLOC];
    ssize_t bytesRead = read(src, buffer, sizeof(buffer));
    ssize_t NbEcrits=0;

    while(bytesRead > 0){
        NbEcrits=write(STDOUT_FILENO,buffer,bytesRead);
        bytesRead = read(src, buffer, sizeof(buffer)); // Mettre à jour bytesRead pour la prochaine itération
    }

    if (bytesRead == -1) {
        perror("bytesRead");
        exit(EXIT_FAILURE);
    }

    if (NbEcrits == -1) {
        perror("NbEcrits");
        exit(EXIT_FAILURE);
    }

    close(src);
}



// Read redir va concaténer le contenu de src dans dest
void read_redir(char src[], char dest[]) {
        int source = open(src, O_RDONLY);
        int destination = open(dest, O_WRONLY | O_CREAT | S_IRUSR | S_IWUSR | S_IRGRP, 0644);
    
    
        if (source == -1) {
            perror(src);
            exit(EXIT_FAILURE);
        }
    
        if (destination == -1) {
            perror(dest);
            exit(EXIT_FAILURE);
        }
    
        char buffer[TAILLE_BLOC];
        ssize_t bytesRead = read(source, buffer, sizeof(buffer));
        ssize_t NbEcrits=0;
    
        while(bytesRead > 0){
            NbEcrits=write(destination,buffer,bytesRead);
            bytesRead = read(source, buffer, sizeof(buffer)); // Mettre à jour bytesRead pour la prochaine itération
        }
    
        if (bytesRead == -1) {
            perror("bytesRead");
            exit(EXIT_FAILURE);
        }
    
        if (NbEcrits == -1) {
            perror("NbEcrits");
            exit(EXIT_FAILURE);
        }
    
        close(source);
        close(destination);

}



int main (int argc,char *argv[]){
    if (argc < 2 ) {
        fprintf(stderr, "Usage: %s fichier [\">\" fichier ]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int redirection = 0;

    for(int i =0;i<argc;i++){
        if((strcmp(argv[i], ">") == 0 && (i == (argc-2)))) {
            redirection = 1;
        }
        break;
    }

    if (redirection==0){
        for(int i=1;i<argc;i++){ // On commence à 1 pour ne pas prendre en compte le nom du programme
            pid_t new_pid = fork();

            if(new_pid ==-1){
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (new_pid==0){
                readbase(argv[i]);
            }
            exit(EXIT_SUCCESS);
        }

    }


    if(redirection==1) {
        for(int i = 1; i < argc - 2; i++) { //La boucle va jusqu'à l'avant dernier argument car le dernier est le fichier de destination 
            pid_t new_pid = fork();

            if(new_pid==-1){
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if(new_pid==0){
                read_redir(argv[i],argv[argc-1]);
            }
            exit(EXIT_SUCCESS);
    }



    return 0;
}
}