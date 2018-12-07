#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

void readLine(char line[]);

int main() {

	char IPAddress[20];
	unsigned int port;
	char userName[20];
	char line[1024] = "";
	char buffer[1024] = "";

	int sockFD = socket(AF_INET, SOCK_STREAM, 0);

	printf("Enter IP:");
	scanf("%s", IPAddress);
	
	printf("Enter port:");
	scanf("%u", &port); 

	printf("Enter user name:\n");
	scanf("%s", userName);

	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, IPAddress, &(address.sin_addr));
	
	connect(sockFD, (struct sockaddr *) &address, sizeof(address));
	getchar();

	while (strcmp(line, "quit") != 0) {
		
		readLine(line);
		sprintf(buffer, "%s: %s", userName, line);
		send(sockFD, buffer, strlen(buffer) + 1, 0);
	}

	return 0; 

}

void readLine(char line[]) {	
	
	int c = 0;	
	int i = 0;

	while((c = getchar()) != '\n') {
		line[i] = c;
		i++;
	}

	line[i] = '\0';

}
