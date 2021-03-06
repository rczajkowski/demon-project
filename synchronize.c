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

#define HUGE_FILE 5

int isFileInDir(const char *path);
char* connect(const char *path, const char *fileName);
void copy(const char *fromPath, const char *toPath);
void mapCopy(const char *fromPath, const char *toPath, size_t fileSize);

void synchronize(const char *sourcePathDir, const char *destinationPathDir){
	syslog(LOG_INFO, "Demon sie obudzil i zaczyna synchronizacje");
	
	DIR *sourceDir;
	DIR *destinationDir;

	struct dirent *file;

	struct stat sourceInfo;
	struct stat destinationInfo;

	sourceDir = opendir(sourcePathDir);
	destinationDir = opendir(destinationPathDir);

	if(sourceDir && destinationDir){
		while((file = readdir(destinationDir)) != NULL){
			char *currentFileName = file->d_name;

			if(isFileInDir(connect(sourcePathDir, currentFileName)) == -1)
				if(remove(connect(destinationPathDir, currentFileName)) == 0)
					syslog(LOG_INFO, "Usunieto z folderu docelowego plik o nazwie: %s", currentFileName);
				else
					syslog(LOG_ERR, "Nie udalo sie usunac pliku z folderu doceleowego o nazwie: %s !!!", currentFileName);
		}


	while((file = readdir(sourceDir)) != NULL){
		char *currentFileName = file->d_name;
		stat(connect(sourcePathDir, currentFileName), &sourceInfo);

		if(sourceInfo.st_mode & S_IFDIR)
			continue;
			
		if( stat(connect(destinationPathDir, currentFileName), &destinationInfo) == -1 || ((sourceInfo.st_mtime) > (destinationInfo.st_mtime)) ){

			if(sourceInfo.st_size >= HUGE_FILE) 
				mapCopy(connect(sourcePathDir, currentFileName), connect(destinationPathDir, currentFileName), sourceInfo.st_size);
			else
				copy(connect(sourcePathDir, currentFileName), connect(destinationPathDir, currentFileName));
		}
				
	}

		
        closedir(sourceDir);
        closedir(destinationDir);
	}

	else{
		syslog(LOG_ERR, "Blad otwarcia folderow!!!");
		syslog(LOG_INFO, "Koniec synchronizacji");
		return;
	}
}
