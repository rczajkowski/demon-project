#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
char* connect(const char *path, const char *fileName){
	char *result = malloc(strlen(path)+strlen(fileName) + 1);
	strcpy(result, path);
	strcat(result, fileName);

	return result;
}

