#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 

int main() {
    struct sockaddr_in client;
    int s, flag;
    char buffer[20];

    s = socket(AF_INET, SOCK_STREAM, 0);
    client.sin_family = AF_INET;
    client.sin_port = htons(2000); 
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(s, (struct sockaddr*)&client, sizeof(client));

    printf("\nEnter a string to check palindrome: "); 
    scanf("%s", buffer); 
    printf("\nClient: %s", buffer); 
    send(s, buffer, sizeof(buffer), 0); 
    recv(s, &flag, sizeof(int), 0); 

    if (flag == 1) 
        printf("\nServer: The string is a Palindrome.\n"); 
    else 
        printf("\nServer: The string is not a palindrome.\n"); 

    close(s); 
    return 0;
}

/* ALOGRITHM
1. Declare variables:
    - s: integer to store the socket descriptor
    - flag: integer to store the result of palindrome check
    - buffer[20]: character array to store the user input string
2. Create a TCP socket:
    - s = socket(AF_INET, SOCK_STREAM, 0)
3. Set up the server address:
    - Initialize the client structure client.sin_family = AF_INET
    - Set the port to 2000 (converted to network byte order): client.sin_port = htons(2000)
    - Set the IP address to localhost: client.sin_addr.s_addr = inet_addr("127.0.0.1")
4. Connect to the server:
    - connect(s, (struct sockaddr*)&client, sizeof(client))
5. Prompt the user to enter a string to check palindrome:
    - Print "Enter a string to check palindrome: "
6. Read the user input string:
    - scanf("%s", buffer)
7. Print the client's input string:
    - Print "Client: " followed by buffer
8. Send the user input string to the server:
    - send(s, buffer, sizeof(buffer), 0)
9. Receive the result of palindrome check from the server:
    - recv(s, &flag, sizeof(int), 0)
10. Check the value of the flag:
    - If flag is equal to 1, print "Server: The string is a Palindrome."
    - Otherwise, print "Server: The string is not a palindrome."
11. Close the socket:
    - close(s)
12. Exit the program with return code 0.
*/
