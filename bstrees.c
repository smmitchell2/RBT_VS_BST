#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "bst.h"
#include "vbst.h"
#include "rbt.h"
#include "scanner.h"
#include "comparator.h"

void displayString(FILE *fp, void *v){
    fprintf(fp, "\"%s\"", (char*)v);
}

void cleanUp(char *word){
    char *src = word, *dst = word;
	while (*src){
	    if(ispunct((unsigned char)*src)){
		    src++;
		}
		else if(isupper((unsigned char)*src)){
			*dst++ = tolower((unsigned char)*src);
			src++;
		}
		else if(isdigit((unsigned char)*src)){
			src++;
		}
		else if(isspace(*src) && isspace(*(src+1))){
			while(isspace(*(src+1))){
				src++;
			}
		}
		else if(isspace(*src)){
			*src = ' ';
			*dst++ = *src++;
		}
		else if(!islower((unsigned char)*src)){
			src++;
		}
		else if(src == dst){
			src++;
			dst++;
		}
		else{
			*dst++ = *src++;
		}
	}
	*dst = 0;
}

int main(int argc, char **argv){
	FILE *data = fopen(argv[2], "r");
	FILE *commands = fopen(argv[3], "r");
	FILE *output = stdout;
	if(argc == 4){
		output = stdout;
	}
	else if(argc == 5){
		output = fopen(argv[4], "w");
	}
	else{
		printf("Invalid number of arguments passed\n");;
		return 0;
	}
	if(strcmp(argv[1], "-r") == 0){
		char variable = readChar(data);
		char *var;
		rbt *r = newRBT(displayString, stringComparator);
		while(!feof(data)){
			if(variable == '"'){
				ungetc(variable, data);
				var = readString(data);
			}
			else{
				ungetc(variable, data);
				var = readToken(data);
			}
			cleanUp(var);
			if(strcmp(var, "") != 0){
				insertRBT(r, var); //issue here
			}
			variable = readChar(data);
		}
		char commandVariable = readChar(commands);
		while(!feof(commands)){
			if(commandVariable == 'i'){
				char *tempCommand;
				commandVariable = readChar(commands);
				if(commandVariable == '"'){
					ungetc(commandVariable, commands);
					tempCommand = readString(commands);
				}
				else{
					ungetc(commandVariable, commands);
					tempCommand = readToken(commands);
				}
				cleanUp(tempCommand);
				if(strcmp(tempCommand, "") != 0){
					insertRBT(r, tempCommand);
				}
			}
			else if(commandVariable == 'd'){
				char *tempCommand;
				commandVariable = readChar(commands);
				if(commandVariable == '"'){
					ungetc(commandVariable, commands);
					tempCommand = readString(commands);
				}
				else{
					ungetc(commandVariable, commands);
					tempCommand = readToken(commands);
				}
				cleanUp(tempCommand);
			}
			else if(commandVariable == 'f'){
				char *tempCommand;
				commandVariable = readChar(commands);
				if(commandVariable == '"'){
					ungetc(commandVariable, commands);
					tempCommand = readString(commands);
				}
				else{
					ungetc(commandVariable, commands);
					tempCommand = readToken(commands);
				}
				cleanUp(tempCommand);
				fprintf(output, "Frequency of \"%s\": %d\n", tempCommand, findRBT(r, tempCommand));
			}
			else if(commandVariable == 's'){
				displayRBT(output, r);
			}
			else if(commandVariable == 'r'){
				statisticsRBT(r, output);
			}
			else{
				printf("Invalid command detected\n");
				return 0;
			}
			commandVariable = readChar(commands);
		}
	}
	else if(strcmp(argv[1], "-v") == 0){
		char variable = readChar(data);
		char *var;
		vbst *v = newVBST(displayString, stringComparator);
		while(!feof(data)){
			if(variable == '"'){
				ungetc(variable, data);
				var = readString(data);
			}
			else{
				ungetc(variable, data);
				var = readToken(data);
			}
			cleanUp(var);
			if(strcmp(var, "") != 0){
				insertVBST(v, var);
			}
			variable = readChar(data);
		}
		char commandVariable = readChar(commands);
		while(!feof(commands)){
			if(commandVariable == 'i'){
				char *tempCommand;
				commandVariable = readChar(commands);
				if(commandVariable == '"'){
					ungetc(commandVariable, commands);
					tempCommand = readString(commands);
				}
				else{
					ungetc(commandVariable, commands);
					tempCommand = readToken(commands);
				}
				cleanUp(tempCommand);
				if(strcmp(tempCommand, "") != 0){
					insertVBST(v, tempCommand);
				}
			}
			else if(commandVariable == 'd'){
				char *tempCommand;
				commandVariable = readChar(commands);
				if(commandVariable == '"'){
					ungetc(commandVariable, commands);
					tempCommand = readString(commands);
				}
				else{
					ungetc(commandVariable, commands);
					tempCommand = readToken(commands);
				}
				cleanUp(tempCommand);
				if(strcmp(tempCommand, "") != 0){
					deleteVBST(v, tempCommand);
				}
			}
			else if(commandVariable == 'f'){
				char *tempCommand;
				commandVariable = readChar(commands);
				if(commandVariable == '"'){
					ungetc(commandVariable, commands);
					tempCommand = readString(commands);
				}
				else{
					ungetc(commandVariable, commands);
					tempCommand = readToken(commands);
				}
				cleanUp(tempCommand);
				fprintf(output, "Frequency of \"%s\": %d", tempCommand, findVBST(v, tempCommand));
			}
			else if(commandVariable == 's'){
				displayVBST(output, v);
			}
			else if(commandVariable == 'r'){
				statisticsVBST(v, output);
			}
			else{
				printf("Invalid command detected\n");
				return 1;
			}
			commandVariable = readChar(commands);
		}
	}
	else{
		printf("Invalid argument.\n");
		return 0;
	}
	return 0;
}
