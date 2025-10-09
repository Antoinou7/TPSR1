#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <errno.h>
#define N 4
#define POSIX_C_SOURCE 200809L 

int est_premier (unsigned long long int n)
{
  if ((n>1) && (n==2 || n==3 || ((n%2)&&(n%3))))
  {
    unsigned long long int i,y;

    y=sqrt(n)+1;
    i=5;
    while(i<y)
    {
      if (n%i == 0)
        return 0;
      i+=2;
      if (n%i == 0)
        return 0;
      i+=4;
    }
    return 1;
  }
  return 0;
}








int main(int argc, char* argv[]){
    int tube[2];

    unsigned long long nblus;

    if(pipe(tube)==-1){
        perror("Echec creation tube");
        exit(2);
    }

    for(int i =0;i<N;i++){
        pid_t pid = fork();
        if (pid==-1){
            perror("Erreur fork");
            exit(1);
        }
        if(pid==0){ /* Contexte du fils */
            close(tube[1]);
            unsigned long long local_count = 0;
            while((read(tube[0],(void*)&nblus,sizeof(nblus)))>0){
                if(est_premier(nblus)==1){
                    printf("[Fils %d]     %llu est premier\n",i,nblus);
                    local_count++;
                } else {
                    printf("[Fils %d]     %llu\n",i,nblus);
                }
                close(tube[0]);
                exit(local_count);
            }
        }
    }
    close(tube[0]);
    for(int i=1;i<argc;i++){
        errno = 0;
        unsigned long long int val = strtoull(argv[i],NULL,10);
        if(write(tube[1],&val,sizeof(val))==-1){
            perror("Echec write du père dans le tube");
            exit(3);
        }
    }
    close(tube[1]);
    
    int nbprems=0;
    for(int i=0;i<N;i++){
        int status;
        wait(&status);
        if(WIFEXITED(status)){
            nbprems+=WEXITSTATUS(status);
        }
    }
    printf("Il y a %d nombre(s) premier(s)\n",nbprems);

    return 0;
}