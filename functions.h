size_t getFileSize(char fileName[]);

const char* getFileExt(char str[]);

void file_get_content(char fileName[], char buffer[]);

char parseFlag(char flag[]);

int arrayClear(char array[], int len);

int writeToEnd(char destination[], char source[], int sourceLen);

void addPrefix(char array[]);

int isFlag(char str[]);

int isCss(char str[]);

void printInfo();

void printFileInfo(char fileName[], size_t fileSize, size_t newFileSize);

void createDirForCompressed(char array[]);

void readToBuffer(FILE *file, char buffer[]);

void compressFile(char fileName[], char targetFileName[], char flag);
