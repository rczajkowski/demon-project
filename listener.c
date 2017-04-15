#include <stdio.h>
#include <signal.h>

void synchronize(const char *sourcePathDir, const char *destinationPathDir);

void listener(int mySignal){
	
	synchronize();
}