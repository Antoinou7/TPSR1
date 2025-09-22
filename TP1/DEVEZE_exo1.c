#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <limits.h>
#define POSIX_C_SOURCE 200809L


void print_proc_info(void) {
    pid_t pid  = getpid();
    pid_t ppid = getppid();
    pid_t pgrp  = getpgrp();

   


    


    printf("Process Information\n");
    printf("-------------------\n");
    printf("PID   : %d\n", pid);
    printf("PPID  : %d\n", ppid);
    printf("PGRP  : %d\n", pgrp);
   


}





int main(){
    print_proc_info();
    

    pid_t new_pid = fork();

    if(new_pid==-1){
        perror("fork");
        exit(1);
    }
    if(new_pid){
        int infofils;
        wait(&infofils);
        printf("Le père a récupéré le code de retour du fils : %d\n", WEXITSTATUS(infofils));
        printf("\nJe suis le père, voici mes informations : \n");
        print_proc_info();
        printf("\nJe suis le père et je me termine, mon code de retour est %d\n", getpid());
        exit(0);
    } else {
        printf("\nJe suis le fils, voici mes informations : \n");
        print_proc_info();
    }
   
    exit(0);

return 0;


}