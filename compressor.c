#include <stdio.h>
#include <string.h>
#include "functions.h"

#define BUFFER_LEN 5000000
#define FILE_NAME_LEN 100

int main(int argc, char **argv) {
	FILE *file;
	char targetFileName[FILE_NAME_LEN];
	char buffer[BUFFER_LEN];
	size_t baseFileSize;
	int fileNameLen;
	char flag;
	
	if ( argv[1] == NULL ) {
		printInfo();
		
		return 0;
	}
	
	strcpy(targetFileName, argv[1]);
	fileNameLen = strlen(targetFileName);
	baseFileSize =  getFileSize(targetFileName);
	flag = parseFlag(argv[2]);
	file = fopen(targetFileName, "r");
	
	readToBuffer(file, buffer);
	
	if ( flag != 'm' ) {
		addPrefix(targetFileName, fileNameLen);
	}
	
	file = fopen(targetFileName, "w");
	fprintf(file, "%s", buffer);
	fclose(file);
	
	printResult(targetFileName, baseFileSize);
	
	return 0;
}
