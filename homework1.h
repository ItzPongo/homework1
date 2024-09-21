#ifndef HOMEWORK1_H
#define HOMEWORK1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

/*
Name: client_echo
Process: Once the client is connected to the server
         it will read what the client sends, print the message
         in the server and then echo it back to the client.
         Must account for the user disconnecting and the message recieve
         failing
Function Input/Parameters: (void* arg)
Function Output/Parameters: command line output
Function Output/Returned: message to echo
Device Input/---: none
Device Output/---: none
Dependencies: none
*/
void* client_echo(void* arg);

/*
Name: main
Process: In charge of the server connection, including the
         socket creation, binding to the port, listening, accepting the connection,
         recv, send and closing
Function Input/Parameters: none
Function Output/Parameters: command line output
Function Output/Returned: message to echo
Device Input/---: none
Device Output/---: none
Dependencies: none
*/
int main(void);

#endif