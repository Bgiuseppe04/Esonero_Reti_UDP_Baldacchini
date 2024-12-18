/*
 ============================================================================
 Name        : Client_Baldacchini.h
 Author      : Baldacchini G.
 Version     :
 Copyright   : Your copyright notice
 Description : Header File of the Client.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include "Controls.h"
#include "Data.h"


#define SIZE 5// Buffer dimension
#define LENGTH 33 //Lenght of the password
#define port 57015 //port
#define SERVER_ADDR  "passwdgen.uniba.it"



