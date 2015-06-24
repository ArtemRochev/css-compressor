#include <stdio.h>
#include "functions.h"

#define ASCII_SPACE 32
#define ASCII_TAB 9
#define ASCII_NEW_LINE 10

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

void readToBuffer(FILE *file, char buffer[]) {
	char scanedValue;
	int counter = 0;
	
	while ( fscanf(file, "%c", &scanedValue) != EOF ) {
		if ( scanedValue != ASCII_SPACE && scanedValue != ASCII_TAB && scanedValue != ASCII_NEW_LINE ) {
			buffer[counter] = scanedValue;
			counter += 1;
		}
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
