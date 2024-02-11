#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
int main(void)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[2000], client_message[2000];
    int server_struct_length = sizeof(server_addr);
    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (socket_desc < 0)
    {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");
    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Get input from the user:
    printf("Enter message: ");
    gets(client_message);
    // Send the message to server:
    if (sendto(socket_desc, client_message, strlen(client_message), 0,
               (struct sockaddr *)&server_addr, server_struct_length) < 0)
    {
        printf("Unable to send message\n");
        return -1;
    }
    // Receive the server's response:
    if (recvfrom(socket_desc, server_message, sizeof(server_message), 0,
                 (struct sockaddr *)&server_addr, &server_struct_length) < 0)
    {
        printf("Error while receiving server's msg\n");
        return -1;
    }
    printf("Server's response: %s\n", server_message);
    // Close the socket:
    close(socket_desc);
    return 0;
}
// ALOGIRITHM
// 1. Declare variables:
//     - socket_desc: integer to store the socket descriptor
//     - server_addr: structure to store server address information
//     - server_message: character array to store server message
//     - client_message: character array to store client message
//     - server_struct_length: integer to store the length of the server address structure

// 2. Initialize server_message and client_message arrays with null characters.

// 3. Create a UDP socket:
//     - socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)

// 4. Check if the socket creation was successful:
//     - If socket_desc < 0, print an error message and return -1.

// 5. Print a success message indicating the socket creation.

// 6. Set up the server address:
//     - server_addr.sin_family = AF_INET
//     - server_addr.sin_port = htons(2000)
//     - server_addr.sin_addr.s_addr = inet_addr("127.0.0.1")

// 7. Prompt the user to enter a message:
//     - Print "Enter message: ".

// 8. Read the message from the user:
//     - Read input into client_message.

// 9. Send the message to the server:
//     - if sendto(socket_desc, client_message, strlen(client_message), 0, (struct sockaddr *)&server_addr, server_struct_length) < 0, print an error message and return -1.

// 10. Receive the response from the server:
//     - if recvfrom(socket_desc, server_message, sizeof(server_message), 0, (struct sockaddr *)&server_addr, &server_struct_length) < 0, print an error message and return -1.

// 11. Print the server's response:
//     - Print "Server's response: " followed by server_message.

// 12. Close the socket:
//     - close(socket_desc)

// 13. Exit the program with return code 0.
