#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include "functions.h"

#define FILE_NAME_LEN 100

int main(int argc, char **argv) {
	FILE *file;
	char flag;
	char targetFileName[FILE_NAME_LEN];
	size_t baseFileSize;
	int fileNameLen;
	
	if ( argc < 2 ) {
		printInfo();
		
		return 0;
	}
	
	if ( isFlag(argv[1]) ) {
		flag = parseFlag(argv[1]);
	} else {
		flag = parseFlag(argv[2]);
		strcpy(targetFileName, argv[1]);
	}
	
	if ( flag == 'a' ) {
		char newDirPath[1024];
		strcpy(targetFileName, "test.css");
		DIR *dir;
		struct dirent *dirent;
		char currentDir[100];
		
		createDirForCompressed(newDirPath);
		
		getcwd(currentDir, sizeof(currentDir));
		
		if ( dir = opendir(currentDir) ) {
			while ( dirent = readdir (dir) ) {
				if ( isCss(dirent->d_name) ) {
					char fileName[100];
					char newFileName[100];
					
					strcpy(fileName, dirent->d_name);
					addPrefix(fileName);
					
					strcpy(newFileName, newDirPath);
					strcat(newFileName, fileName);
					
					compressFile(dirent->d_name, newFileName, flag);
					printFileInfo(fileName, getFileSize(dirent->d_name), getFileSize(newFileName));
				}
			}
			
			closedir (dir);
		}
	} else if ( !isFlag(argv[1]) ) {
		size_t baseSize = getFileSize(targetFileName);
		
		if ( flag != 'm' ) {
			addPrefix(targetFileName);
		}
		
		compressFile(argv[1], targetFileName, flag);
		printFileInfo(argv[1], baseSize, getFileSize(targetFileName));
	}
	
	return 0;
}
