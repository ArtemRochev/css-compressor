size_t getFileSize(char fileName[]);

char parseFlag(char flag[]);

int arrayClear(char array[], int len);

int addPrefix(char array[], int len);

void arrayShift(char array[], int len, int offset);

void printInfo();

void printResult(char fileName[], size_t baseFileSize);

void readToBuffer(FILE *file, char buffer[]);
