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


//     ALGORITHM
//     1. Declare variables:
//     - socket_desc: integer to store the socket descriptor
//     - server_addr: structure to store server address information
//     - client_message: character array to store the message to be sent to the server
//     - server_message: character array to store the message received from the server

// 2. Initialize client_message and server_message arrays with null characters.

// 3. Create a TCP socket:
//     - socket_desc = socket(AF_INET, SOCK_STREAM, 0)

// 4. Check if the socket creation was successful:
//     - If socket_desc < 0, print an error message and return -1.

// 5. Print a success message indicating the socket creation.

// 6. Set up the server address:
//     - server_addr.sin_family = AF_INET
//     - server_addr.sin_port = htons(2000)
//     - server_addr.sin_addr.s_addr = inet_addr("127.0.0.1")

// 7. Connect to the server:
//     - if connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0, print an error message and return -1.

// 8. Print a success message indicating the connection.

// 9. Prompt the user to enter a message:
//     - Print "Enter the message: ".

// 10. Read the message from the user:
//     - gets(client_message).

// 11. Send the message to the server:
//     - if send(socket_desc, client_message, strlen(client_message), 0) < 0, print an error message and return -1.

// 12. Receive a response from the server:
//     - if recv(socket_desc, server_message, sizeof(server_message), 0) < 0, print an error message and return -1.

// 13. Print the server's response:
//     - Print "Server res: " followed by server_message.

// 14. Close the socket:
//     - close(socket_desc).

// 15. Exit the program with return code 0.
