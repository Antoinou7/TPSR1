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
    return 0;





}