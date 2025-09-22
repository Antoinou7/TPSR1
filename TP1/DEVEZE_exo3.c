#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <decoupe.h>
#define POSIX_C_SOURCE 200809L

int main (int argc, char* argv[]){
    char* tab [NBMOTSMAX+1];
    for(int i=1; i<argc; i++){
        char* cmd = argv[i];
        Decoupe(cmd,tab);
        pid_t new_pid = fork();

        if(new_pid==-1)
        {
            perror("fork");
            exit(1);
        }
         if (new_pid)
        {
            printf("[%d] Je délègue %s a %d. J'attends sa fin\n",getpid(),cmd,new_pid);
            wait(NULL);
            printf("[%d] : %dtermine\n",getpid(),pid);
        }
         else{

         
            printf("[%d] je lance %s :\n",getpid(),cmd);
            execvp(tab[0],tab);       
        }
       
    }
printf("J'ai fini\n");
}