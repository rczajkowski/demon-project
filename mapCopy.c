#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <syslog.h>
#include <stdlib.h>

void mapCopy(const char *fromPath, const char *toPath, size_t fileSize){
	syslog(LOG_INFO, "Mapowanie z %s do %s", fromPath, toPath);
        
	int file;
	int fileToSave;

	file = open(fromPath, O_RDONLY, 0);
        if(file < 0){
	    	syslog(LOG_ERR, "Blad otwarcia pliku %s!!!", fromPath);
		syslog(LOG_INFO, "Koniec programu");
	    	return;
	}

        void* mmappedData = mmap(NULL, fileSize, PROT_READ, MAP_PRIVATE | MAP_POPULATE, file, 0);
        if(mmappedData == MAP_FAILED){
		close(file);
		syslog(LOG_ERR, "Blad mapowania pliku %s", fromPath);
		return;	
	}

        
	fileToSave = open(toPath, O_WRONLY | O_CREAT,  00700);
	if(fileToSave < 0){
	    	syslog(LOG_ERR, "Blad otwarcia pliku %s!!!", toPath);
		return;
	}
  
	if(write(fileToSave, mmappedData, fileSize) < 0){
            		syslog(LOG_ERR, "Blad zapisu!!!");
			close(file);
			close(fileToSave);
			munmap(mmappedData, fileSize);
			return;
	}

        int rc = munmap(mmappedData, fileSize);
        if(rc < 0){
		syslog(LOG_ERR, "Blad usuwania mapowania!!!");
		close(file);
		close(fileToSave);
		return;	
	}

        close(file);
	close(fileToSave);
}
