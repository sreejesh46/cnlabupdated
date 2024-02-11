Here's the beautified version of the code with proper indentation and spacing:

```c
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int socket_desc;
    struct sockaddr_in server_addr, client_addr;
    char client_message[2000], server_message[2000];

    memset(client_message, '\0', sizeof(client_message));
    memset(server_message, '\0', sizeof(server_message));

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc < 0) {
        printf("\nError while creating the socket..");
        return -1;
    }
    printf("\nSocket created successfully.");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("\nCannot connect...");
        return -1;
    }

    printf("\nConnected successfully.");

    printf("\nEnter the message: ");
    gets(client_message);

    if (send(socket_desc, client_message, strlen(client_message), 0) < 0) {
        printf("\nCannot send the message");
        return -1;
    }

    if (recv(socket_desc, server_message, sizeof(server_message), 0) < 0) {
        printf("\nCould not receive the message...");
        return -1;
    }

    printf("\nServer res: %s\n", server_message);

    close(socket_desc);
    return 0;
}
```
