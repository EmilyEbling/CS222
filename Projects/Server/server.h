#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void sendHead(int socket, int length, char* type);
void sendGet(int socket, char* message, int read);

#endif


