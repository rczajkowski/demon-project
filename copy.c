#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

void copy(const char *fromPath, const char *toPath){
    int file;
    int fileToSave;

    char buf[BUF_SIZE];

    file = open(fromPath, O_RDONLY,0);

	if(file < 0){
	    printf("Blad odczytu pliku odczyt\n");
	    return 0;
	}

	fileToSave = open(toPath, O_WRONLY | O_CREAT,  00700);
	if(fileToSave < 0){
	    printf("Blad odczytu pliku zapis\n");
	    return 0;
	}

	int ssize;

	while((ssize=read(file, buf, BUF_SIZE)) != 0){
	    if(ssize < BUF_SIZE)
            buf[ssize] = '\0';

        //printf("odczytano %d: %s \n \n", ssize,buf);
		if(write(fileToSave, buf, ssize) < 0)
            perror("Write error:");
            break;
	}

	close(file);
	close(fileToSave);
}
