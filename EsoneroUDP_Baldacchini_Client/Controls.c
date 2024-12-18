/*
 ============================================================================
 Name        : Controls.c
 Author      : Baldacchini G.
 Version     :
 Copyright   : Your copyright notice
 Description : Definitions of the controls
 ============================================================================
*/
#ifndef Controls
#define	Controlsh

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "Controls.h"

#define LENGHT 32
/**
 * @brief Verifies and parses user input for type and length.
 * This function checks if the input string contains a valid type and length value,
 * and assigns them to the respective output parameters.
 *
 * @param[in] i The input string to parse. Expected format: "<type> <length>",
 *              where <type> is a character and <length> is an integer.
 * @param[out] t Pointer to a character where the parsed type will be stored (output parameter).
 * @param[out] l Pointer to an integer where the parsed length will be stored (output parameter).
 *
 * @return `true` if the input is valid and successfully parsed; `false` otherwise.
 *         If the input is invalid, an error message is printed.
 */
bool verifyinputvalue(char i[],char* t,int* l) //input , type and length
{
	if (sscanf(i, " %c %d", t, l) != 2) {
	 printf("The input is not valid. Re-insert it!\n");
	 return false;
	 }else return true;
}

/**
 * @brief Checks if the input string is the quit command ("q").
 * This function compares the input string with the character "q" to determine if the user wants to quit.
 * If the input matches, it prints a confirmation message and returns `true`.
 *
 * @param[in] v The input string to verify.
 *
 * @return `true` if the input is "q" (case-sensitive), indicating a quit command; `false` otherwise.
 */
bool verifyifq(char v[]){

	if (strcmp(v, "q") == 0) {
	    printf("OK! I'm closing the process...\n");
		return true;
	 }else return false;
}

/**
 * @brief Checks if the input string is the menu command ("h").
 * This function compares the input string with the character "h" to determine if the user needs help.
 * If the input matches, it returns `true`.
 *
 * @param[in] v The input string to verify.
 *
 * @return `true` if the input is "h" (case-sensitive), indicating help command; `false` otherwise.
 */
bool verifyifh(char v[]){

	if (v[0] == 'h') {
		return true;
	 }else return false;
}

/**
 * @brief Verifies if a character is one of the valid predefined characters.
 * This function checks whether the given character matches any of the valid characters ('n', 'a', 'm', 's','u','h').
 *
 * @param[in] character The character to verify.
 *
 * @return `true` if the character is valid; `false` otherwise.
 */
bool verifyFirstCharacter(char character)
{
    char validCharacters[] = {'n', 'a', 'm', 's','u','h'};
    for (int i = 0; i < 6; i++) {
        if (character == validCharacters[i]) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Verifies if the length of the password is within the valid range.
 * This function checks whether the provided length is between 6 and a predefined maximum length (LENGHT).
 *
 * @param[in] length The length of the password to verify.
 *
 * @return `true` if the length is valid (between 6 and LENGHT); `false` otherwise.
 *         If the length is invalid, an error message is printed.
 */
bool lenght_of_password(int length)
{
	if(length < 6 || length > LENGHT)
	{
		puts("Enter a length between 6 and 32 characters.\n");
		return false;
	}
	else return true;
}

/**
 * @brief Checks if the input string contains any spaces.
 * This function iterates through the input string and returns `true` if it finds a space character.
 *
 * @param[in] input The input string to check for spaces.
 *
 * @return `true` if the string contains at least one space; `false` otherwise.
 */
bool verifySpaces(char* input)
{
    while (*input) {
        if (*input == ' ') {
            return true;
        }
        input++;
    }
    return false;
}

/**
 * @brief Verifies if the choice matches one of the two valid values.
 * This function checks if the provided choice is equal to either of the two valid values.
 *
 * @param[in] choice The character choice to verify.
 * @param[in] value1 The first valid value to compare against.
 * @param[in] value2 The second valid value to compare against.
 *
 * @return `true` if the choice matches either value1 or value2; `false` otherwise.
 *         If the choice is invalid, an error message is printed.
 */
bool verifychoice(char choice, char  value1, char value2) {
    if (choice==value1||choice==value2) {
        return true;
    }
    else{
    	puts("The choice value inserted is not valid.");
    	return false;
    }
}

/**
 * @brief Verifies if the choice matches the exit value.
 * This function checks if the provided choice is equal to the specified exit value.
 * If it matches, it prints a confirmation message and returns `true`.
 *
 * @param[in] choice The character choice to verify.
 * @param[in] value3 The exit value to compare against.
 *
 * @return `true` if the choice matches the exit value; `false` otherwise.
 *         If the choice matches, a message is printed confirming the exit.
 */
bool verifyexit(char choice, char value3){
	if(choice==value3){
		printf("OK! I'm closing the process...\n");
				return true;
			 }else
				 return false;
	}

/**
 * @brief Clears the input buffer.
 * This function reads and discards characters from the input buffer until a newline character (`\n`) or EOF is encountered.
 * It is typically used to clean up any leftover input after reading data from the user.
 */
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Displays a menu and retrieves the user's choice for generating another password or quitting.
 * This function prompts the user to choose whether to generate another password or quit the program.
 * The user's input is captured and returned as a character.
 *
 * @return The user's choice as a character:
 *         - 'y' to generate another password.
 *         - 'q' to quit the program.
 */
/*char printmenuchoice(){
	char choice;
	printf("Wanna generate another password?\n"
			"Press:"
			"\n\t y if you wanna do it"
			"\n\t q if you wanna quit."
			"\n");

	scanf(" %c", &choice);
	clear_input_buffer(choice);
	return choice;
}*/

char printmenuchoice() {
    char choice;

    while (1) {
        printf("Wanna generate another password?\n"
               "Press:"
               "\n\t y if you wanna do it"
               "\n\t q if you wanna quit."
               "\n");

        scanf(" %c", &choice);  // Legge un singolo carattere


        // Controlla se il carattere inserito è più di uno
        if (getchar() != '\n') {
            printf("Error: Please enter only one character.\n");
            clear_input_buffer();  // Pulisce di nuovo il buffer
        } else {
            // Se l'input è valido, esce dal ciclo
            break;
        }
    }

    return choice;
}


#endif



