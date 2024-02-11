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

// ALGORITHM
// 1. Declare variables:
//     - socket_desc: integer to store the socket descriptor
//     - client_sock: integer to store the client socket descriptor
//     - client_size: integer to store the size of the client address structure
//     - server_addr: structure to store server address information
//     - client_addr: structure to store client address information
//     - client_message: character array to store the message received from the client
//     - server_message: character array to store the message to be sent to the client

// 2. Initialize client_message and server_message arrays with null characters.

// 3. Create a TCP socket:
//     - socket_desc = socket(AF_INET, SOCK_STREAM, 0)

// 4. Check if the socket creation was successful:
//     - If socket_desc < 0, print an error message using perror() and return -1.

// 5. Set up the server address:
//     - server_addr.sin_family = AF_INET
//     - server_addr.sin_port = htons(2000)
//     - server_addr.sin_addr.s_addr = inet_addr("127.0.0.1")

// 6. Bind the socket to the server address and start listening for incoming connections:
//     - If bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 or listen(socket_desc, 1) < 0,
//       print an error message using perror() and return -1.

// 7. Print a message indicating that the server is listening for incoming connections.

// 8. Accept incoming connection requests from clients:
//     - client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size)

// 9. Check if the connection was successful:
//     - If client_sock < 0, print an error message using perror() and return -1.

// 10. Print a message indicating that the server has connected to the client.

// 11. Receive a message from the client:
//     - if recv(client_sock, client_message, sizeof(client_message), 0) < 0, print an error message using perror() and return -1.

// 12. Print the message received from the client.

// 13. Prepare the server message to be sent to the client:
//     - strcpy(server_message, "This is server's message")

// 14. Send the server message to the client:
//     - if send(client_sock, server_message, strlen(server_message), 0) < 0, print an error message using perror() and return -1.

// 15. Close the client socket and the server socket:
//     - close(client_sock)
//     - close(socket_desc)

// 16. Exit the program with return code 0.


