// server program for udp connection 
#include <stdio.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#define PORT 5000 
#define MAXLINE 1000 

// Driver code 
int main() 
{ 
	char buffer[100]; 
	char *message = "Hello Client"; 
	int listenfd, len; 
	struct sockaddr_in servaddr, cliaddr; 
	bzero(&servaddr, sizeof(servaddr)); 

	// Create a UDP Socket 
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);		 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_family = AF_INET; 

	// bind server address to socket descriptor 
	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
	
	//receive the datagram 
	len = sizeof(cliaddr); 
	int n = recvfrom(listenfd, buffer, sizeof(buffer), 
			0, (struct sockaddr*)&cliaddr,&len); //receive message from server 
	buffer[n] = '\0'; 
	puts(buffer); 
		
	// send the response 
	sendto(listenfd, message, MAXLINE, 0, 
		(struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
} 
/*
1. Initialize variables:
    - buffer[100]: to store incoming data
    - message: a string to send to the client
    - listenfd: socket file descriptor for listening
    - servaddr: structure to store server address information
    - cliaddr: structure to store client address information
    - len: variable to store the length of client address
    - PORT: constant integer representing the port number
    - MAXLINE: constant integer representing the maximum length of a message

2. Clear the servaddr structure using bzero().

3. Create a UDP socket:
    listenfd = socket(AF_INET, SOCK_DGRAM, 0)

4. Set up the server address:
    servaddr.sin_family = AF_INET
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY)
    servaddr.sin_port = htons(PORT)

5. Bind the server address to the socket descriptor:
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr))

6. Receive the datagram from the client:
    len = sizeof(cliaddr)
    n = recvfrom(listenfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len)
    buffer[n] = '\0'

7. Print the received message:
    puts(buffer)

8. Send the response message (message) to the client:
    sendto(listenfd, message, MAXLINE, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr))

9. Close the socket:
    close(listenfd)
*/
