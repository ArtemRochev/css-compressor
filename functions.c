#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
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

size_t getFileSize(char fileName[]) {
	struct stat st;
	
	stat(fileName, &st);
	
	return st.st_size;
}

void arrayShift(char array[], int len, int offset) {
	int last = len - 1;
	
	for ( int i = last; i >= 0; i-- ) {
		array[i+offset] = array[i];
	}
}

void printInfo() {
	printf("Compress CSS file.\n");
	printf("Removing spaces, tabs, new line charters.\n\n");
	printf("Usage:\n");
	printf("./compressor.out <file_name>\n\n");
	printf("-m    modified source file\n");
}

void printResult(char fileName[], size_t baseFileSize) {
	size_t diff = baseFileSize - getFileSize(fileName);
	
	printf("Compressed: %s\n", fileName);
	
	if ( baseFileSize >= 1024 ) {
		printf("   base: %zd kb\n", baseFileSize / 1024);
		printf("   min:  %zd kb\n", getFileSize(fileName) / 1024);
	} else {
		printf("   base: %zd bytes\n", baseFileSize);
		printf("   min:  %zd bytes\n", getFileSize(fileName));	
	}
	
	if ( diff >= 1024 ) {
		printf("   diff: %zd kb\n", diff / 1024);
	} else {
		printf("   diff: %zd bytes\n", diff);
	}
}

int arrayClear(char array[], int len) {
	for ( int i = 0; i < len; i++ ) {
		array[i] = (char) 0;
	}
	
	return 0;
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
				for ( int i = 0; i < strlen(importantPartBuffer); i++ ) {
					buffer[counter] = importantPartBuffer[i];
					counter += 1; 
				}
				
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

char parseFlag(char flag[]) {
	if ( flag == NULL ) {
		return (char) 0;
	}
	
	if ( flag[0] == '-') {
		if ( flag[1] == 'm' ) {
			return 'm';
		}
	}
	
	return (char) 0;
}

int addPrefix(char array[], int len) {
	int prefixLen = 4;
	
	arrayShift(array, len, prefixLen);
	
	array[0] = 'm';
	array[1] = 'i';
	array[2] = 'n';
	array[3] = '.';
	
	return len + prefixLen;
}
