#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int socket_desc, client_sock, client_size;
    struct sockaddr_in server_addr, client_addr;
    char client_message[2000], server_message[2000];

    memset(client_message, '\0', sizeof(client_message));
    memset(server_message, '\0', sizeof(server_message));

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0) {
        perror("\nError creating socket");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 ||
       listen(socket_desc, 1) < 0) {
        perror("\nBinding or listening error");
        return -1;
    }

    printf("\nListening for incoming connections...");

    client_size = sizeof(client_addr);
    client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
    if(client_sock < 0) {
        perror("\nCan't connect to the client");
        return -1;
    }

    printf("\nConnected at IP: %s and port %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    if(recv(client_sock, client_message, sizeof(client_message), 0) < 0) {
        perror("\nError receiving message");
        return -1;
    }
    printf("\nMsg from client: %s\n", client_message);

    strcpy(server_message, "This is server's message");

    if(send(client_sock, server_message, strlen(server_message), 0) < 0) {
        perror("\nError sending message");
        return -1;
    }

    close(client_sock);
    close(socket_desc);

    return 0;
}
