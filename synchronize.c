#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

int isFileInDir(const char *path);
char* connect(const char *path, const char *fileName);
void copy(const char *fromPath, const char *toPath);

void synchronize(const char *sourcePathDir, const char *destinationPathDir){
    DIR *sourceDir;
    DIR *destinationDir;

    struct dirent *file;

    struct stat sourceInfo;
    struct stat destinationInfo;

    sourceDir = opendir(sourcePathDir);
    destinationDir = opendir(destinationPathDir);

    if(sourceDir && destinationDir){
            if((file = readdir(destinationDir)) == NULL){

                while((file = readdir(sourceDir)) != NULL){
                    char *currentFileName = file->d_name;
                    stat(connect(sourcePathDir, currentFileName), &sourceInfo);

                    if(sourceInfo.st_mode & S_IFDIR)
                            continue;

                    copy(connect(sourcePathDir, currentFileName), connect(destinationPathDir, currentFileName));
                }

            }
	

		while((file = readdir(destinationDir)) != NULL){
			char *currentFileName = file->d_name;

			if(isFileInDir(connect(sourcePathDir, currentFileName)) == -1)
				remove(connect(destinationPathDir, currentFileName));

		}


            while((file = readdir(sourceDir)) != NULL){
                char *currentFileName = file->d_name;
                stat(connect(sourcePathDir, currentFileName), &sourceInfo);

                if(sourceInfo.st_mode & S_IFDIR)
                        continue;

                stat(connect(destinationPathDir, currentFileName), &destinationInfo);

                if((sourceInfo.st_mtime) > (destinationInfo.st_mtime))
                    copy(connect(sourcePathDir, currentFileName), connect(destinationPathDir, currentFileName));
		
		
            }



        closedir(sourceDir);
        closedir(destinationDir);
    }
    else
        perror("Error:");

}

