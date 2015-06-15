#include <stdio.h>

#define ASCII_SPACE 32
#define ASCII_TAB 9
#define ASCII_NEW_LINE 10

#define BUFFER_LEN 500000

int addPrefix(char *array) {
	array[0] = 'm';
	array[1] = 'i';
	array[2] = 'n';
	array[3] = '.';
	
	return 4;
}

int main(int argc, char **argv) {
	if ( argv[1] == NULL ) {
		printf("Compress CSS file.\n");
		printf("Removing spaces, tabs, new line charters.\n\n");
		printf("Usage:\n");
		printf("%s <file_name>\n\n", argv[0]);
		printf("-m    modified getting file\n");
		
		return 0;
	}
	
	FILE *file;
	char fileNameToCompress[100];
	char buffer[BUFFER_LEN];
	char scanedValue;
	int prefixLen = 0;
	int counter = 0;
	
	file = fopen(argv[1], "r");
	
	while ( fscanf(file, "%c", &scanedValue) != EOF ) {
		if ( scanedValue != ASCII_SPACE && scanedValue != ASCII_TAB && scanedValue != ASCII_NEW_LINE ) {
			buffer[counter] = scanedValue;
			
			printf("%d - %c\n", scanedValue, scanedValue);
			
			counter += 1;
		}
	}
	
	if ( argv[2] != NULL ) {
		if ( argv[2][0] == '-') {
			if ( argv[2][1] != 'm' ) {
				prefixLen = addPrefix(fileNameToCompress);
				printf("Unknow option.\n");
			}
		}
	} else {
		prefixLen = addPrefix(fileNameToCompress);
	}
	
	for (int i = 0; i < sizeof(argv[1]); i++ )	{
		fileNameToCompress[i+prefixLen] = argv[1][i];
	}
	
	
	file = fopen(fileNameToCompress, "w");
	
	fprintf(file, "%s", buffer);
	
	printf("Compressed: %s\n", fileNameToCompress);
	
	return 0;
}