#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

void hi_handler(int code){
    fprintf(stderr, "Signal %d caught\n", code);
    fprintf(stderr, "Hi\n");
}
int main(int argc, char**argv){

    struct sigaction hi_action;
    hi_action.sa_handler = hi_handler;
    hi_action.sa_flags = 0;
    sigemptyset(&hi_action.sa_mask);
    sigaddset(&hi_action.sa_mask, SIGINT); //adds SIGINT to the list of blocks to sa_mask
    sigprocmask(SIG_BLOCK, &hi_action.sa_mask, NULL); //makes sa_mask all of type SIG_BLOCK
    //basically adds sigint into a block type signal+
    sigaction(SIGUSR1, &hi_action, NULL); //old act = NULL
    //old_act => the old of what it does stored in old_act

    while (1){
        printf("Not hi");
        sleep(10);
    }

}