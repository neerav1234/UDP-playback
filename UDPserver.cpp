// Server side implementation of UDP client-server model
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
using namespace std;
	
#define PORT	 8080
#define MAXLINE 1024
	
// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
    // char exitt[MAXLINE];
    string s = "exit";
    // for(int i = 0; i < 4; i++){
    //     exitt[i] = s[i];
    // }
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		// cout << sizeof(cliaddr) << endl;
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
		
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
		
	int len, n;
	
	len = sizeof(cliaddr); //len is value/result
    // cout << len << endl;
	while(true){
        memset(buffer, 0, sizeof(buffer));
        n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                    MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                    (socklen_t*) &len);
        buffer[n] = '\0';
        printf("Client : %s\n", buffer);
        memset(buffer, 0, sizeof(buffer));
        cin >> buffer;
        // if(buffer == exitt){
        //     close(sockfd);
	    //     return 0;
        // }
        bool ex = true;
        for(int i = 0; i < 4; i++){
            if(buffer[i] != s[i]){
                ex = false;
            }
        }
        
        sendto(sockfd, (const char *)buffer, strlen(buffer),
            MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
                len);
        // printf("Hello message sent.\n");
        if(ex){
                perror("Connection Terminated by Server");
                exit(EXIT_FAILURE);
                return 0;
        }
    }
		
	return 0;
}
