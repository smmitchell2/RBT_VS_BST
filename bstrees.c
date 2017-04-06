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

char *grammar(char *word){
  int i;
  int spot = 0;
  char *newWord = malloc(sizeof(char)*strlen(word)+1);
  for(i = 0; i < (int) strlen(word); i++){
    if(isalpha(word[i])){
      spot = 0;
      word[i] = tolower(word[i]);
      sprintf(newWord,"%s%c",newWord,word[i]);
    }
    else if(isspace(word[i]) && spot == 0){
      sprintf(newWord,"%s ",newWord);
      spot = 1;
    }
  }
  return newWord;
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
		char *word;
		rbt *r = newRBT(displayString, stringComparator);
		while(!feof(data)){
			if(variable == '"'){
				ungetc(variable, data);
				word = readString(data);
			}
			else{
				ungetc(variable, data);
				word = readToken(data);
			}
			word = grammar(word);
			if(strcmp(word, "") != 0){
				insertRBT(r, word);
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
				grammar(tempCommand);
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
				tempCommand = grammar(tempCommand);
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
				tempCommand = grammar(tempCommand);
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
		char *word;
		vbst *v = newVBST(displayString, stringComparator);
		while(!feof(data)){
			if(variable == '"'){
				ungetc(variable, data);
				word = readString(data);
			}
			else{
				ungetc(variable, data);
				word = readToken(data);
			}
			word = grammar(word);
			if(strcmp(word, "") != 0){
				insertVBST(v, word);
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
				tempCommand = grammar(tempCommand);
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
				tempCommand = grammar(tempCommand);
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
				tempCommand = grammar(tempCommand);
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
