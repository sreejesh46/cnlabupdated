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
1. Create a TCP socket (s).
2. Configure the server address:
    - Set the address family to AF_INET.
    - Set the port to 2000 (converted to network byte order).
    - Set the IP address to localhost (127.0.0.1).
3. Bind the socket to the server address.
4. Set the socket to listen for incoming connections, with a backlog queue size of 1.
5. Accept a connection from a client, creating a new socket (sock) for communication.
6. Repeat indefinitely:
    7. Receive a string from the client on the socket (sock).
    8. Print the received string.
    9. Check if the received string is empty:
        - If it is empty, set the flag to indicate a palindrome (flag = 1).
        - Otherwise, iterate through the string to check if it's a palindrome:
            - Initialize left pointer to the beginning of the string and right pointer to the end.
            - While left < right and flag is true:
                - If characters at left and right positions are not equal, set flag to 0 (indicating not a palindrome).
                - Otherwise, move left pointer to the right and right pointer to the left.
    10. Send the flag back to the client indicating whether the received string is a palindrome or not.
    11. Break the loop (terminate the server after processing one request).
7. Close the communication socket (sock).
8. Close the listening socket (s).
9. Exit the program.
*/
