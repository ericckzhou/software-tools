//SC
//write & read
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT 50055

int main(){
    int sock_fd  = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1){
        perror("socket");
    }
    //sockaddr_in for bind, connect, etc.
    struct sockaddr_in peer;
    peer.sin_family = AF_INET;
    peer.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &peer.sin_addr);
    if (connect(sock_fd, (struct sockaddr *)&peer, sizeof(peer)) == -1){
        fprintf(stderr, "connect error\n");
    }
    char buf[128];
    int r = read(fileno(stdin), buf, 128);
    buf[r] = '\0';
    write(sock_fd, buf, sizeof(buf));

    char in[256];
    int i = read(sock_fd, in, sizeof(in));
    in[i] = '\0';
    printf("Read from server: %s\n", in);

    close(sock_fd);
    return 0;
}