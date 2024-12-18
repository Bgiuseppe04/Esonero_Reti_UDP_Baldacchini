/*
 ============================================================================
 Name        : Server_Baldacchini.h
 Author      : Baldacchini Giuseppe
 Version     :
 Copyright   : Your copyright notice
 Description : Header File of the Server
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#include "Data.h"

#define SIZEOFBUFFER 4
#define SIZEOFPASSWORD 33

#define port 57015 //port number




