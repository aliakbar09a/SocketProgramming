#include<stdio.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define BUFFER_SIZE 1024
#define PORT 8080 

int main()
{
	struct sockaddr_in server_addr;
	int sockfd, ret;
	char buffer[BUFFER_SIZE];
	// creating socket 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("\nError creating socket");
		exit(0);
	}
	printf("\nSuccessfully created socket");
	// assigning 0's to server_addr structure
	memset(&server_addr, '0', sizeof(server_addr));
	//assigning values to server_addr structure
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	// converting ip from presentation to network
	if(inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr)) <= 0)
	{
		printf("\nError attaching local address\n");
		exit(0);
	}
	if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("\nConnect Failed");
		exit(0);
	}
	printf("\nConnection Established\n");
	printf("\nEnter the number : ");
	scanf("%s", buffer);
	send(sockfd, buffer, strlen(buffer), 0);
	printf("\nNumber is sent\n");
	read(sockfd, buffer, strlen(buffer));
	printf("The squared number is : %s \n", buffer);
	
}
