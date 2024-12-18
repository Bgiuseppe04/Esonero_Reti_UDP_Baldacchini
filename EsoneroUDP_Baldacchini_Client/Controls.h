/*
 ============================================================================
 Name        : Controls.h
 Author      : Baldacchini G.
 Version     :
 Copyright   : Your copyright notice
 Description : Header File of the Controls.
 ============================================================================
 */
#ifndef Controls
#define Controls_H

#include <stdbool.h>

bool verifyinputvalue(char i[],char* t,int* l);
bool verifyifq(char v[]);
bool verifyifh(char v[]);
bool verifyFirstCharacter(char character);
bool lenght_of_password(int length);
bool verifySpaces(char* input);
bool verifychoice(char choice , char value1, char value2);
bool verifyexit(char choice, char value3);
void clear_input_buffer();
char printmenuchoice();
#endif
