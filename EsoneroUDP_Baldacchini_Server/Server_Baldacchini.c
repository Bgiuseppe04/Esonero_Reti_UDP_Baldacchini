/*
 ============================================================================
 Name        : Server_Baldacchini.c
 Author      : Baldacchini G.
 Version     :
 Copyright   : Your copyright notice
 Description : Server File of the Project
 ============================================================================
 */

#include "Server_Baldacchini.h"
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

void errorhandler(char *error_message) {
printf("%s",error_message);
}

//Functions prototypes
void generate_alpha(const char **collection, int* l);
void generate_secure(const char **collection, int* l);
void generate_mixed(const char **collection, int* l);
void password_simulator(char t, int l, char *pass);
void generate_numeric(const char **collection, int* l);
void generate_unambiguous(const char **collection , int*l);

//main function
int main(void) {
#if defined WIN32 // Winsock Inizialitation
WSADATA wsa_data;
if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
errorhandler("WSAStartup failed.");
return 0;}
#endif
//Inizialitation of the srand function
srand(time(NULL));
int sck; //socket
sck = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP); //socket creation

if (sck < 0) {
	errorhandler("The creation of the socket is failed.\n");
	clearwinsock();
return -1;}

struct sockaddr_in sad; 	//sockaddr_in is the type of the variable sad
sad.sin_family = AF_INET;   //IPv4
sad.sin_addr.s_addr = inet_addr( "127.0.0.1" );
sad.sin_port = htons( 57015 );

//Association
if (bind(sck, (struct sockaddr*) &sad, sizeof(sad)) < 0 ) {
	errorhandler("bind() failed.\n");
	closesocket(sck);	//closing of the socket
	clearwinsock();
	return -1;
}

printf("The server is ready to listen\nThe port on which the server is ready to listen is %d . . .\n", port);

struct sockaddr_in cad; //struct for client address
unsigned int client_len = sizeof(cad);
int c_socket;

client_input var;//structure
char password[SIZEOFPASSWORD];

while (1){
	int bites;
	//Stamp  of the address and the port
while(1){
	bites=recvfrom(sck,(void*)&var,sizeof(var),0,(struct sockaddr*)&cad,&client_len);
	if (bites>0){
		printf("\n\nNew request from %s:%d\n", inet_ntoa(cad.sin_addr), ntohs(cad.sin_port));
	}

	var.l = ntohl(var.l);
	printf("\n\nRequest from client %c %d\n", var.t, var.l);
	password_simulator(var.t, var.l, password);

	if (sendto(sck,password, strlen(password), 0,(struct sockaddr*)&cad,client_len) < 0) {
		perror("The send of the password is failed.");}
	else printf("The response has been sent . . .");}
        }


    closesocket(c_socket);
    closesocket(sck);
	#if defined WIN32
    system("pause");
	#endif
        exit(0);
}

/**
 * @brief Simulates an alphabetic collection.
 * This function assigns a pointer to a static alphabetic string and sets the length of the alphabet.
 *
 * @param[out] collection Pointer to the alphabet string (output parameter).
 * @param[out] l Pointer to an integer where the length of the alphabet will be stored (output parameter).
 */
void generate_alpha(const char **collection, int* l){
static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
*collection = alphabet;
*l = sizeof(alphabet) - 1;}

/**
 * @brief Simulates a secure password character collection.
 * This function assigns a pointer to a static string containing characters suitable for secure passwords
 * and sets the length of the character collection.
 *
 * @param[out] collection Pointer to the character collection string (output parameter).
 * @param[out] l Pointer to an integer where the length of the character collection will be stored (output parameter).
 */
void generate_secure(const char **collection, int* l){
static const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=,./<>?";
*collection = characters;
*l = sizeof(characters) - 1;
}

/**
 * @brief Simulates a mixed collection of letters and numbers.
 * This function assigns a pointer to a static string containing lowercase letters and digits,
 * and sets the length of the character collection.
 *
 * @param[out] collection Pointer to the character collection string (output parameter).
 * @param[out] l Pointer to an integer where the length of the character collection will be stored (output parameter).
 */
void generate_mixed(const char **collection, int* l){
static const char letters_numbers[] = "abcdefghijklmnopqrstuvwxyz0123456789";
*collection = letters_numbers;
*l = sizeof(letters_numbers) - 1;
}
/**
 * @brief Generates a random password based on the specified type and length.
 * This function creates a password by randomly selecting characters from a specified character set.
 * The character set is determined by the type parameter (`t`), and the password is stored in the provided buffer.
 *
 * @param[in] t The type of password to generate:
 *              - 'n': Numeric characters only.
 *              - 'a': Alphabetic characters only.
 *              - 'm': Mixed alphabetic and numeric characters.
 *              - 's': Secure password with alphanumeric and special characters.
 *              - 'u': Unambiguous password without ambiguous characters.
 *              - 'h': Help Menu.
 * @param[in] ln The desired length of the password.
 * @param[out] pass Pointer to the buffer where the generated password will be stored.
 *                  The buffer must be large enough to hold the password and the null terminator.
 */
void password_simulator(char t, int ln, char *pass) {
const char *charset;
int lset;

switch (t) {
        case 'n':
        	generate_numeric(&charset, &lset);
        	break;
        case 'a':
        	generate_alpha(&charset, &lset);
            break;
        case 'm':
        	generate_mixed(&charset, &lset);
            break;
        case 's':
        	generate_secure(&charset, &lset);
            break;
        case 'u':
        	generate_unambiguous(&charset, &lset);
        	break;
        default:
            snprintf(pass, SIZEOFPASSWORD, "The password has not been generated.");
            return;
    }

	int random;
    for (int j = 0; j < ln; j++) {
    random=	rand() % lset;
        pass[j] = charset[random];
    }
    pass[ln] = '\0';
}

/**
 * @brief Simulates a numeric character collection.
 * This function assigns a pointer to a static string containing numeric digits (0-9)
 * and sets the length of the character collection.
 *
 * @param[out] collection Pointer to the numeric character collection string (output parameter).
 * @param[out] l Pointer to an integer where the length of the numeric character collection will be stored (output parameter).
 */
void generate_numeric(const char **collection, int* l){
	static const char numbers[] = "0123456789";
	*collection = numbers;
	*l = sizeof(numbers) - 1;
}

void generate_unambiguous(const char **collection, int*l){
	static const char unambchar[]="ACDEFGHJKLMNPQRTUVWXYabcdefghjkmnpqrtuvwxy34679!@#$%^&*()_+-=,./<>?";
	*collection=unambchar;
	*l= sizeof(unambchar)-1;
}



