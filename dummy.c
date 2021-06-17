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

int global;

void handler1(int code){
    kill(global, code);
}
int main(){
    int n = fork();
    if (n==0){
        execl("./dummy2", "dummy2", NULL);
        return 1;
    }
    else {
        global = n;
        struct sigaction s;
        s.sa_handler = handler1;
        sigemptyset(&s.sa_mask);
        s.sa_flags=0;
        sigaction(SIGUSR1, &s, NULL);
        int w, status;
        w = waitpid(n, &status, 0);
        if (WIFEXITED(status)){
            printf("exit code: %d\n", WEXITSTATUS(status));
        }
    }
    return 0;
}