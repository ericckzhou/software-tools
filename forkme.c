#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    printf("%s %s\n", argv[0], argv[1]);
    char *print[5] = {"Please", "Say", "Hi", "To", "Me"};
    int n, m;
    pid_t w;
    int status;
    int i = 0 ;
    for (i = 0; i < 5; i++){
        n=fork();
        if (n == 0){
            break;
        }
    }
    for (int j = 0; j < 5; j++){
        w = wait(&status);
        if (WIFEXITED(status)){
            printf("%s\n", print[j]);
        }
    }
    int input;
    if (n==0 && i==4){
        scanf("%d", &input);
        exit(input);
    }
    if (n > 0 && i == 5){
        printf("%d\n", WEXITSTATUS(status));
    }
    return 0;
}
//rule of thumb: handle child first, then praent process

//wait waits for child tot finish
//but child did not print outside itself. instead it printed
//when it waits
//fix: print in child process
