/*
 ============================================================================
 Name        : Client_Baldacchini.c
 Author      : Baldacchini G.
 Version     :
 Copyright   : Your copyright notice
 Description : Client File of the Project
 ============================================================================
*/

#include "Client_Baldacchini.h"

void printmenu();
/**
 * @brief Shuts down the Windows Sockets library.
 * This function is intended for use on Windows systems. It releases
 * all resources allocated by the Windows Sockets API.
*/

void clearwinsock() {
#if defined WIN32
    WSACleanup();
#endif
}

/**
* @brief Manages errors by displaying a specific message.
* This function prints an error message to the standard output to report an issue in the program.
* @param[in] error_message: the error message to display.
*/

void errorhandler(char *errorMessage) {
    printf("%s", errorMessage);
}

int main(void) {

// Winsock inizialitation
#if defined WIN32
WSADATA wsa_data;

if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
errorhandler("WSAStartup failed.");
return 0;}
#endif

int c_socket;
// socket creation
c_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
if (c_socket < 0) {
errorhandler("The creation of the socket is failed.\n");
clearwinsock();
return -1;}
//Resolution
struct hostent *server;
    server = gethostbyname(SERVER_ADDR);
    	 if (server == NULL) {
    	     fprintf(stderr, "Error, no such host\n");
    	     exit(EXIT_FAILURE);}
// struct for server address
struct sockaddr_in server_addr;
//set to zero the entire structure
memset(&server_addr, 0, sizeof(server_addr));
// N.B : The address is  IPv4.
server_addr.sin_family = AF_INET;
// IP adress configuration
memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
// Server port is 57015
server_addr.sin_port = htons(57015);

char password[LENGTH];
char buffer_input[SIZE]; //size of the input of the user
unsigned int serverlength=sizeof(server_addr);
while (1){
bool flagforclose = false; //this flag is for the closing function
bool flagclosing=false;
bool flagmenu= false; //this flag is for the input if the choice is h
bool flagrepeat;
client_input var; //structure for the message
do{ flagrepeat=false;
	printf("\nEnter the type of the password followed by  a space and the length of the password.\n"
            "Press:\n"
			"\t a for an alphabetic password,\n"
            "\t n for a numeric password,\n"
            "\t s for a secure password,\n"
            "\t m for a mixed password.\n"
			"\t u for an unambiguous password.\n"
			"\t h for the Help Menu.\n"
            "\t    Instead, if you want to close the process , press q.\n");
do{
memset(buffer_input, 0, sizeof(buffer_input));
fgets(buffer_input, SIZE, stdin);
//verify if the first character is h
if(verifyifh(buffer_input)){
	printmenu();
	flagmenu=true;
	printf("\nEnter the type of the password followed by  a space and the length of the password.\n");
	continue;
}
else flagmenu=false;
//Newline character remotion
buffer_input[strcspn(buffer_input, "\n")] = '\0';

if(verifyifq(buffer_input)){
flagforclose = true;
flagclosing=true;
break;}

if(flagforclose) break;
}
while(flagmenu);
if(flagclosing) break;

if(!verifySpaces(buffer_input)){
printf("Input format not valid. Insert again following the instructions! \n");
flagrepeat=true;
continue;}

// Validate input
if(!verifyinputvalue(buffer_input,&var.t,&var.l)){
	fflush(stdin);
	flagrepeat=true;
continue;}
fflush (stdin);

if(!verifyFirstCharacter(var.t)){
printf("The character %c inserted is not valid. Insert again! \n", var.t);
continue;}
}
while(!lenght_of_password(var.l) || !verifyFirstCharacter(var.t));
if(flagrepeat)continue;
if(flagclosing) break;
//host to network
var.l = htonl(var.l);

if (sendto(c_socket, (void*)&var, sizeof(var), 0, (struct sockaddr *)&server_addr, serverlength) < 0) { //probabile cambiare server con server_addr
    perror("Error in sendto");
    break;
}

var.l= ntohl(var.l);

printf("The request has been sent. The type  is %c and the length is %d\n", var.t, var.l);
int value = recvfrom(c_socket,password,LENGTH, 0,
                          (struct sockaddr *)&server_addr,&serverlength);
if (value < 0) {
    perror("Error in recvfrom");
    // Gestisci l'errore qui
} else {
    printf("Received %d bytes from server.\n", value);
}
if (value > 0) {
password[value] = '\0';
printf("The password generated by the server is : %s\n", password);}
else {
printf("There was an error in receiving the password.\n");
break;}

memset(password, 0, sizeof(password));
bool flag;
bool result;
do{
	flag=false;
	result=true;
	char choice=printmenuchoice(); //return the choice

	 result=verifychoice(choice, 'y', 'q'); //return true or false

	if (choice == 'y') {
	            puts("Continuing...");
	            continue;}
	if(choice=='q'){
	            verifyexit(choice, 'q');
	            flag=true;
	            break;

	        }
}while (!result);
if (flag) break;
}
closesocket(c_socket);
clearwinsock();
#if defined WIN32
system("pause");
#endif
exit(0);
}

void printmenu() {
    const char *help_menu =
        "Password Generator Help Menu\n"
        "Commands:\n"
        " h        : show this help menu\n"
        " n LENGTH : generate numeric password (digits only)\n"
        " a LENGTH : generate alphabetic password (lowercase letters)\n"
        " m LENGTH : generate mixed password (lowercase letters and numbers)\n"
        " s LENGTH : generate secure password (uppercase, lowercase, numbers, symbols)\n"
        " u LENGTH : generate unambiguous secure password (no similar-looking characters)\n"
        " q        : quit application\n\n"
        "LENGTH must be between 6 and 32 characters\n\n"
        "Ambiguous characters excluded in 'u' option:\n"
        " 0 O o (zero and letters O)\n"
        " 1 l I i (one and letters l, I)\n"
        " 2 Z z (two and letter Z)\n"
        " 5 S s (five and letter S)\n"
        " 8 B (eight and letter B)\n";

    printf("%s", help_menu);
}


