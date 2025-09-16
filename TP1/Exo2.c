#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define POSIX_C_SOURCE 200809L



int main()
{

int pid=fork();
if (pid==-1){ /* Echec du fork */
perror("fork");
exit(1);
}

if(pid){
execl("/bin/date","date",NULL);
perror("date");
exit(1);

}else{ /* on est dans le premier fils */
execl("/bin/ls", "ls", "-al", NULL);
perror("ls");
exit(2);
}





}
