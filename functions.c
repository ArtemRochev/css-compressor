#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "functions.h"

#define ASCII_SPACE 32
#define ASCII_TAB 9
#define ASCII_NEW_LINE 10

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
		printf("  | base: %zd kb\n", baseFileSize / 1024);
		printf("  | min:  %zd kb\n", getFileSize(fileName) / 1024);
	} else {
		printf("  | base: %zd bytes\n", baseFileSize);
		printf("  | min:  %zd bytes\n", getFileSize(fileName));	
	}
	
	if ( diff >= 1024 ) {
		printf("  | diff: %zd kb\n", diff / 1024);
	} else {
		printf("  | diff: %zd bytes\n", diff);
	}
}

void readToBuffer(FILE *file, char buffer[]) {
	char scanedValue;
	int counter = 0;
	bool isScope = false;
	
	while ( fscanf(file, "%c", &scanedValue) != EOF ) {
		if ( scanedValue == '\'' && !isScope ) {
			isScope = true;
		} else if ( scanedValue == '\'' ) {
			isScope = false;
		}
		
		if ( scanedValue != ASCII_SPACE && scanedValue != ASCII_TAB && scanedValue != ASCII_NEW_LINE || isScope ) {
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
