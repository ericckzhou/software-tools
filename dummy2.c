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

#define EXIT_STATUS 5

void handler1(int code){
    printf("Killed process child\n");
    exit(1);
}
int main(){
    struct sigaction s;
    s.sa_handler = &handler1;
    sigemptyset(&s.sa_mask);
    s.sa_flags=0;
    sigaction(SIGUSR1, &s, NULL);
    while (1){
            printf("dummy1\n");
            sleep(10);
    }
}