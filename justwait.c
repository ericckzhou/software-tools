#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
    int n=fork();
    if (n== 0){
        while(1){

        }
        exit(0);
    }
    //wait forever.
    int w, status;
    w=wait(&status);
    if (WIFEXITED(status)){
        printf("Waited: %d\n", status);
        return WEXITSTATUS(status);
    }
    printf("%d\n", w);
    return -1;
}