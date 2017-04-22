#include <dirent.h>
#include <errno.h>

int isDir(const char* path){
	DIR *dir = opendir(path);
	
	if(dir){
		closedir(dir);
		return 1;
	}
	else if(ENOENT == errno){
		return -1;
	}
}
