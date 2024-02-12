#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/stat.h> 
#include <sys/types.h> 

int main() {
    struct sockaddr_in client, server;
    int s, n, sock, flag;
    char b1[20];

    s = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(2000); // Use htons to convert port to network byte order
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(s, (struct sockaddr*)&server, sizeof(server));
    listen(s, 1);
    n = sizeof(client);

    sock = accept(s, (struct sockaddr*)&client, &n);
    for (;;) {
        recv(sock, b1, sizeof(b1), 0);
        printf("\nThe string received is: %s\n", b1);
        if (strlen(b1) == 0)
            flag = 1;
        else {
            int left = 0;
            int right = strlen(b1) - 1;
            flag = 1;
            while (left < right && flag) {
                if (b1[left] != b1[right])
                    flag = 0;
                else {
                    left++;
                    right--;
                }
            }
        }
        send(sock, &flag, sizeof(int), 0);
        break;
    }
    close(sock);
    close(s);
    return 0;
}


/*ALGORITHM
1. Declare variables:
    - s: integer to store the socket descriptor
    - n: integer to store the size of the client address structure
    - sock: integer to store the client socket descriptor
    - flag: integer to store the result of palindrome check
    - b1[20]: character array to store received string
2. Create a TCP socket:
    - s = socket(AF_INET, SOCK_STREAM, 0)
3. Set up the server address:
    - Initialize the server structure server.sin_family = AF_INET
    - Set the port to 2000 (converted to network byte order): server.sin_port = htons(2000)
    - Set the IP address to localhost: server.sin_addr.s_addr = inet_addr("127.0.0.1")
4. Bind the socket to the server address:
    - bind(s, (struct sockaddr*)&server, sizeof(server))
5. Listen for incoming connections:
    - listen(s, 1)
6. Accept incoming connection requests from clients:
    - sock = accept(s, (struct sockaddr*)&client, &n)
7. Receive a string from the client:
    - recv(sock, b1, sizeof(b1), 0)
8. Print the received string:
    - Print "The string received is: " followed by b1.
9. Check if the received string is a palindrome:
    - If the length of the string is 0, set flag to 1.
    - Otherwise, initialize left to 0 and right to strlen(b1) - 1. Set flag to 1.
    - Iterate while left is less than right and flag is true:
        - If b1[left] is not equal to b1[right], set flag to 0.
        - Otherwise, increment left and decrement right.
10. Send the flag (result of palindrome check) to the client:
    - send(sock, &flag, sizeof(int), 0)
11. Close the client socket:
    - close(sock)
12. Close the server socket:
    - close(s)
13. Exit the program with return code 0.
*/
