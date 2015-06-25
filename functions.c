#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include "functions.h"

#define ASCII_SPACE 32
#define ASCII_TAB 9
#define ASCII_NEW_LINE 10
#define ASCII_BACK_SLASH 92
#define ASCII_SINGLE_SCOPE 39
#define ASCII_SCOPE_OPEN 123
#define ASCII_SCOPE_CLOSE 125
#define ASCII_DOUBLE_DOT 58
#define ASCII_SEMICOLON 59

#define true 1
#define false 0
#define BUFFER_LEN 5000000

size_t getFileSize(char fileName[]) {
	struct stat st;
	
	stat(fileName, &st);
	
	return st.st_size;
}

const char* getFileExt(char str[]) {
	char *ext;

  	ext = strrchr (str, '.');

  	if ( ext != NULL ) {
  	    return ext;
	}
	
  	return "";
}

char parseFlag(char flag[]) {
	if ( flag == NULL ) {
		return (char) 0;
	}
	
	if ( flag[0] == '-') {
		return flag[1];
	}
	
	return (char) 0;
}

int arrayClear(char array[], int len) {
	for ( int i = 0; i < len; i++ ) {
		array[i] = (char) 0;
	}
	
	return 0;
}

int writeToEnd(char destination[], char source[], int sourceLen) {
	int destinationLen = strlen(destination);
	
	for ( int i = 0; i < sourceLen; i++ ) {
		destination[destinationLen] = source[i];
		destinationLen += 1; 
	}
	
	return destinationLen;
}

void addPrefix(char array[]) {
	char result[100] = "min.";
	
	strcat(result, array);
	strcpy(array, result);
}

int isFlag(char str[]) {
	if ( str[0] == '-' && strlen(str) == 2 ) {
		return true;
	}
	
	return false;
}

int isCss(char str[]) {
	if ( strcmp(getFileExt(str), ".css") == 0 ) {
		return true;
	}
	
	return false;
}

void printInfo() {
	printf("Compress CSS file.\n");
	printf("Removing spaces, tabs, new line charters.\n\n");
	printf("Usage:\n");
	printf("./compressor.out <file_name>\n\n");
	printf("-a    compress all css files in dir and put in new /min dir\n");
	printf("-m    modified source file\n");
}

void printFileInfo(char fileName[], size_t fileSize, size_t newFileSize) {
	size_t diff =  newFileSize - fileSize;
	
	printf("Compressed: %s\n", fileName);
	
	if ( fileSize >= 1024 ) {
		printf("            %zd kb\n", diff/1024);
	} else {
		printf("            %zd bytes\n", diff);
	}
}

void createDirForCompressed(char array[]) {
	char newDirPath[100];
	
	getcwd(newDirPath, sizeof(newDirPath));
	writeToEnd(newDirPath, "/min/", 5);
	mkdir(newDirPath, S_IRWXU);
	strcpy(array, newDirPath);
}

void readToBuffer(FILE *file, char buffer[]) {
	int importantPartBufferCounter = 0;
	int counter = 0;
	char importantPartBuffer[30];
	char prevScanedSymbol;
	char prevWritedSymbol;
	char scanedSymbol;
	bool isImportantPart = true;
	bool isStr = false;
	
	while ( fscanf(file, "%c", &scanedSymbol) != EOF ) {
		if ( scanedSymbol == ASCII_SINGLE_SCOPE && !isStr ) {
			isStr = true;
		} else if ( scanedSymbol == ASCII_SINGLE_SCOPE && prevScanedSymbol != ASCII_BACK_SLASH ) {
			isStr = false;
		}
		
		if ( scanedSymbol != ASCII_SPACE && scanedSymbol != ASCII_TAB && scanedSymbol != ASCII_NEW_LINE || isStr ) {
			if ( scanedSymbol == ASCII_SCOPE_OPEN || scanedSymbol == ASCII_SEMICOLON ) {
				importantPartBufferCounter = arrayClear(importantPartBuffer, importantPartBufferCounter);
				isImportantPart = false;
			}
			
			if ( isImportantPart && importantPartBufferCounter > 0 ) {
				counter = writeToEnd(buffer, importantPartBuffer, importantPartBufferCounter);
				arrayClear(importantPartBuffer, importantPartBufferCounter);
				importantPartBufferCounter = 0;
			}
			
			buffer[counter] = scanedSymbol;
			counter += 1;
			
			if ( prevWritedSymbol == ASCII_SCOPE_CLOSE || prevWritedSymbol == ASCII_DOUBLE_DOT ) {
				isImportantPart = true;
			}
			
			prevWritedSymbol = scanedSymbol;
		} else if ( isImportantPart ) {
			importantPartBuffer[importantPartBufferCounter] = scanedSymbol;
			importantPartBufferCounter += 1;
		}
		
		prevScanedSymbol = scanedSymbol;
	}
}

void compressFile(char fileName[], char targetFileName[], char flag) {
	FILE *file = fopen(fileName, "r");
	int baseFileSize =  getFileSize(fileName);
	char buffer[BUFFER_LEN];
	
	readToBuffer(file, buffer);
	file = fopen(targetFileName, "w");
	fprintf(file, "%s", buffer);
	
	fclose(file);
}
