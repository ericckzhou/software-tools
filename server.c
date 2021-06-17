#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>    /* Internet domain header */
//SBLA
//read and write


#define PORT 50055
#define MAX_BACKLOG 5 //max connections at once in queue for connecting 

void serve_client(int fd){
    char *msg = "Here you go. Have a good day!\r\n";
    char buf[128];

    int num_read = read(fd, buf, 127);
    buf[num_read] = '\0';
    printf("Server received order: %s\n", buf); 
    char out[256];
    strncpy(out, "Received order: ", 64);
    strncat(out, buf, 128);
    write(fd, out, strlen(out));

}


int main(){
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0); //setting up socket file descriptor.
    struct sockaddr_in server; //setup for bind
    server.sin_family = AF_INET; //family = type of protocol = TCP = INET
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY; //INTERNET ADDRESS ANY communicate on any network interface.
    memset(&server.sin_zero, 0, sizeof(server.sin_zero));  // Initialize sin_zero to 0
    //need to change to struct sockaddr * of server
    //binding address of server (type sockaddr_in) to sock_fd
    //assigning address to socket
    if (bind(sock_fd, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) == -1){
        perror("bind");
    }
    printf("Listening on %d\n", PORT);
    //create queue in kernel for listening to new connection requests.
    //max = 5
    listen(sock_fd, MAX_BACKLOG);
    int client_fd = accept(sock_fd, NULL, NULL);
    printf("Got a new connection!\n");
    serve_client(client_fd);
    close(client_fd);
    close(sock_fd);
    return 0;
}
