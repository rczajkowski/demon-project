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
#include <signal.h>

char *sourcePathDir;
char *destinatioPathDir;

void synchronize(const char *sourcePathDir, const char *destinationPathDir);
int isDir(const char* path);
void listener(int mySignal);

int main(int args, char *argv[]){
	int napTime = 10;
	
	openlog("Demonix", LOG_PID, LOG_USER);
	
	if(args <= 2 || args > 4){
		syslog(LOG_ERR,"Nieodpowiednia ilosc argumentow!!!");
		exit(1);
	}
	
	else if(args >= 3 && args <= 4){
		
		if(isDir(argv[1]) == -1 || access(argv[1],0)){
			syslog(LOG_ERR, "Podana siciezka(%s) nie jest folderem lub brak dostepu!!!", argv[1]);
			exit(1);
		}
		if(isDir(argv[2]) == -1 || access(argv[1],0)){
			syslog(LOG_ERR, "Podana siciezka(%s) nie jest folderem lub brak dostepu!!!", argv[2]);
			exit(1);
		}
		
		if(args == 4)
			napTime = atoi(argv[3]);
		
		sourcePathDir = argv[1];
		destinatioPathDir = argv[2];
		syslog(LOG_INFO, "Folder zrodlowy: %s, folder docelowy: %s", sourcePathDir, destinatioPathDir);
	}
	else{
		syslog(LOG_ERR, "Cos poszlo nie tak...");
		syslog(LOG_INFO, "Koniec programu");
		exit(1);
	}
	
		

	signal(SIGUSR1, listener);
	
	while(1){
		syslog(LOG_INFO,"Demon zasypia na %d s", napTime);
		sleep(napTime);
		synchronize(sourcePathDir, destinatioPathDir);
	}

	closelog();
    return 0;
}

void listener(int mySignal){
	syslog(LOG_INFO, "Wybudzono demona sygnałem SIGUSR1");
	synchronize(sourcePathDir, destinatioPathDir);
}
