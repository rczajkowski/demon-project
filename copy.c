#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>

#define BUF_SIZE 1024

void copy(const char *fromPath, const char *toPath){
	syslog(LOG_INFO, "Zaczeto kopiowanie z %s do %s", fromPath, toPath);
	
    int file;
    int fileToSave;

    char buf[BUF_SIZE];

    file = open(fromPath, O_RDONLY,0);

	if(file < 0){
	    syslog(LOG_ERR, "Blad otwarcia pliku %s!!!", file);
		syslog(LOG_INFO, "Koniec programu");
	    exit(1);
	}

	fileToSave = open(toPath, O_WRONLY | O_CREAT,  00700);
	if(fileToSave < 0){
	    syslog(LOG_ERR, "Blad otwarcia pliku %s!!!", fileToSave);
		syslog(LOG_INFO, "Koniec programu");
		exit(1);
	}

	int ssize;

	while((ssize=read(file, buf, BUF_SIZE)) != 0){
	    if(ssize < BUF_SIZE)
            buf[ssize] = '\0';

        
		if(write(fileToSave, buf, ssize) < 0){
            syslog(LOG_ERR, "Blad zapisu!!!");
			syslog(LOG_INFO, "Koniec programu");
			close(file);
			close(fileToSave);
			exit(1);
		}
	}

	close(file);
	close(fileToSave);
}