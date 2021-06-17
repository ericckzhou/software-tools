#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv){
    printf("%s %s\n", argv[0], argv[1]);
    execl("./forkme", "forkme", NULL);
    //path to file exe, filename, args
    return 0;
    /*
    int p[2];
    pipe(p);
    pid_t pid;
    n = fork();
    //child writes to parent
    if (n == 0){
        close(p[0]); //close read child
        char username[20], password[20];
        scanf("%s", &username);
        scanf("%s", &password);
        write(p[1], username, sizeof(username));
    }
    else{ //>0 not neg assume successful
*/



}