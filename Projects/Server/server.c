
#include "server.h"

int main(int argc, char** argv) {

	int i;
	int dir = 0;
	int value = 1;

	char readPort[1024]; 
	char path[1024];
	char buffer[1024];
	char method[1024];
	char protocol[1024];
	char filepath[1024];

	char* url;

	FILE* file;

	struct stat buf;

	struct sockaddr_in address;
	struct sockaddr_storage otherAddress;

	socklen_t otherSize = sizeof(otherAddress);

	if (argc != 3) { //if there aren't three arguments
		printf("Usage: ./server <port> <path to root>\r\n");
		return -1;
	}

	for (i = 0; argv[1][i] != '\0'; i++) //reads the port number from the command line
        readPort[i] = argv[1][i];
    
    for (i = 0; argv[2][i] != '\0'; i++) //reads the path from the command line
        path[i] = argv[2][i];
    
	path[i] = '\0';

	unsigned int port = atoi(readPort); //changes port to an int

	dir = chdir(path); //change the directory 

	if (dir == -1) { //if the directory could not be changed
		printf("Could not change to directory: %s\r\n", path);
		return -1; 
	}

	int serverSocket = socket(AF_INET, SOCK_STREAM, 0); //create socket

	setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));

	//sets up the address
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = INADDR_ANY;
	bind(serverSocket, (struct sockaddr*)&address, sizeof(address));

	listen(serverSocket, 1); //listens for connection

	while (1) { //infinite loop

		int otherSocket = accept(serverSocket, (struct sockaddr*)&otherAddress, &otherSize); //accepts connection
		printf("Got a client:\r\n");
	
		int length = recv(otherSocket, buffer, sizeof(buffer) - 1, 0); //recieve command
		buffer[length] = '\0';

		printf("\t%s\n", buffer);	

		sscanf(buffer, "%s %s %s", method, filepath, protocol);	//parses buffer into method, filepath, and protocol

		if (filepath[strlen(filepath) - 1] == '/') //if the file path ends with /, add index.html
			strcat(filepath, "index.html");

		if (filepath[0] == '/') //if the file path starts with /, skip that character
			url = &filepath[1];

		else //otherwise no changes need to be made to filepath
			url = filepath;
		
		int status = stat(url, &buf); //used to get size of file (content-length)
		int size = buf.st_size;

		if (status == -1) { //if the path is invalid
			char* message = "HTTP/1.0 404 Not Found\r\n\r\n"; //error message
			send(otherSocket, message, strlen(message), 0); 
			
			if (strcmp(method, "GET") == 0) { //doesn't work
				char getMessage[4096];
				sprintf(getMessage, "<HTML><HEAD><TITLE>404 Not Found</TITLE></HEAD><BODY><H1>Not Found</H1>The requested URL %s was not found on this server.<P>\r\n", url);
				send(otherSocket, getMessage, strlen(getMessage), 0);	
			}
			printf("File not found: %s\r\n\r\n", url);
		}

		else { //otherwise the path is valid

			char* type = strrchr(url, '.');
			type = &type[1]; //get the type of the file

			if (strcmp(method, "HEAD") == 0) { //if head command
				printf("Sent head: %s\r\n\r\n", url);
				sendHead(otherSocket, size, type); //send head info
			}

			else if (strcmp(method, "GET") == 0) { //if get command
				printf("Sent file: %s\r\n\r\n", url);				
				sendHead(otherSocket, size, type); //send head info				
				file = fopen(url, "r+"); //open file
				long fileSize;
				fseek(file, 0, SEEK_END); //go to end of file
				fileSize = ftell(file); //current value of file position
				rewind(file); //sets to beginning of file
				char message[1024];
				int bytesRead = 0;
				do { //keep reading and sending bytes in chunks at a time until file is done
					bytesRead = fread(message, 1, 1024, file);	
					sendGet(otherSocket, message, bytesRead);
				} while(bytesRead == 1024);
				fclose(file);
			}

			else 
				printf("Unknown command: %s\r\n\r\n", method);
		
		}
 
		close(otherSocket);	 

	}

	close(serverSocket);

	return 0;

}

void sendHead(int socket, int  length, char* type) { //send head info

	char* message = "HTTP/1.0 200 OK\r\n";
	char fileLength[1024];
	char fileType[1024];

	sprintf(fileLength, "Content-Length: %d\r\n", length); //length of file

	if (strcmp(type, "html") == 0 || strcmp(type, "htm") == 0) //determines type of file
		sprintf(fileType, "Content-Type: text/html\r\n\r\n"); 

	else if (strcmp(type, "jpg") == 0 || strcmp(type, "jpeg") == 0)
		sprintf(fileType, "Content-Type: image/jpeg\r\n\r\n");
 
	else if (strcmp(type, "gif") == 0)
		sprintf(fileType, "Content-Type: image/gif\r\n\r\n");

	else if (strcmp(type, "png") == 0)
		sprintf(fileType, "Content-Type: image/png\r\n\r\n");

	else if (strcmp(type, "txt") == 0 || strcmp(type, "c") == 0 || strcmp(type, "h") == 0)
		sprintf(fileType, "Content-Type: text/plain\r\n\r\n");
		
	else if (strcmp(type, "pdf") == 0)
		sprintf(fileType, "Content-Type: application/pdf\r\n\r\n");

	send(socket, message, strlen(message), 0); //sends ok message
	send(socket, fileLength, strlen(fileLength), 0); //sends content length
	send(socket, fileType, strlen(fileType), 0); //sends file type

}

void sendGet(int socket, char* message, int read) { //send file information used in GET command

    int sent = 0;
	int size = read;
	char* temp = message;

	do { //send chunks of file at a time, while keeping track of the end of the file
		sent += send(socket, temp, size, 0);
		temp = &message[sent]; //where the message should start each time it is sent
		size-= sent;
	} while (sent != read);	//while what's being sent is not equal to the size of the file

}




















