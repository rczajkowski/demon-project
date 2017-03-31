#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

void synchronize(const char *sourcePathDir, const char *destinationPathDir);

int main(int args, char *argv[]){
    char *sourcePathDir = "dir/";
    char *destinatioPathDir = "dir2/";

    synchronize(sourcePathDir, destinatioPathDir);

    return 0;
}

