#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char**argv){
    if (argc != 2){
        fprintf(stderr, "usage: pipe <child amount>\n");
        exit(1);
    }
    int num_child = atoi(argv[1]);
    //creating pipes for each child
    int p[num_child][2]; 

    for (int i =0; i < num_child; i++){
        pipe(p[i]);
        int n = fork();
        if (n == 0){
            close(p[i][0]); //close read curr child

            for (int j = 0; j < i; j++){
                close(p[j][0]); //close all prev read of prev child
            }
            char msg[20] = "Hello from child";
            write(p[i][1], msg, 20);
            close(p[i][1]);
            exit(0);
        }
    }
    int status;
    int w;
    char buffer[20];
    for (int i = 0; i < num_child; i++){
        /*w = wait(&status);
        if (WIFEXITED(status)){
            printf("status code: %d\n", WEXITSTATUS(status));
        }
        no need to wait, read does a block for u
        */ 
        if (read(p[i][0], &buffer, sizeof(buffer)) == -1){
            fprintf(stderr, "read error");
        }
        printf("read from child %d: %s\n", i, buffer);
    }
}