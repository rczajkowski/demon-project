#include <dirent.h>
#include <errno.h>

int isDir(const char* path){
	DIR *dir = opendir(path);
	
	if(dir){
		puts("istnieje folder \n");
		closedir(dir);
		return 1;
	}
	else if(ENOENT == errno){
		puts("nie iestnieje folder \n");
		return -1;
	}
}