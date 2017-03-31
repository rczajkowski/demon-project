#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int isFileInDir(const char *path){
	int file;
	if(((file = open(path, O_RDONLY,0)) < 0 )){
		close(file);
		return -1;
	}
	else{
		return 1;
	}
}
