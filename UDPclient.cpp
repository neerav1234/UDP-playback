// Client side implementation of UDP client-server model
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <bits/stdc++.h>

using namespace std;
	
#define PORT	 8080
#define MAXLINE 1024
	
// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from client";
	struct sockaddr_in	 servaddr;
     string s = "exit";
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
		
	int n, len;
		while(true){
            memset(buffer, 0, sizeof(buffer));
            cin >> buffer;
            sendto(sockfd, (const char *)buffer, strlen(buffer),
                MSG_CONFIRM, (const struct sockaddr *) &servaddr,
                    sizeof(servaddr));
            // printf("Hello message sent.\n");
            memset(buffer, 0, sizeof(buffer));
                    
            n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                        MSG_WAITALL, (struct sockaddr *) &servaddr,
                        (socklen_t*) &len);
            buffer[n] = '\0';
            bool ex = true;
            for(int i = 0; i < 4; i++){
                if(buffer[i] != s[i]){
                    ex = false;
                }
            }
            if(ex){
                perror("Connection Terminated by Server");
                exit(EXIT_FAILURE);
                return 0;
        }
            printf("Server : %s\n", buffer);
        }
	close(sockfd);
	return 0;
}
