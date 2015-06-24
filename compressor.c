#include <stdio.h>
#include <string.h>
#include "functions.h"

#define BUFFER_LEN 500000
#define FILE_NAME_LEN 100

int main(int argc, char **argv) {
	FILE *file;
	char targetFileName[FILE_NAME_LEN];
	char buffer[BUFFER_LEN];
	char flag;
	int fileNameLen;
	
	if ( argv[1] == NULL ) {
		printInfo();
		
		return 0;
	}
	
	strcpy(targetFileName, argv[1]);
	fileNameLen = strlen(targetFileName);
	flag = parseFlag(argv[2]);
	file = fopen(targetFileName, "r");
	
	readToBuffer(file, buffer);
	
	if ( flag != 'm' ) {
		addPrefix(targetFileName, fileNameLen);
	}
	
	file = fopen(targetFileName, "w");
	fprintf(file, "%s", buffer);
	
	printf("Compressed: %s\n", targetFileName);
	
	return 0;
}
