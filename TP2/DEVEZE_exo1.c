#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define POSIX_C_SOURCE 200809L
#define TAILLE_BLOC 512


void ecrire_dans_stdout(char nom_fich[]){
    int src = open(nom_fich, O_RDONLY);
   
   
    if (src == -1) {
        perror(nom_fich);
        exit(EXIT_FAILURE);
    }

    char buffer[TAILLE_BLOC];
    ssize_t bytesRead = read(src, buffer, sizeof(buffer));
    ssize_t NbEcrits=0;

    while(bytesRead > 0){
        NbEcrits=write(STDOUT,buffer,bytesRead);
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








int main(int argc, char* argv[]) {


}