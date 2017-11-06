#include <time.h>
#include <unistd.h>
#include <stdio.h>

void myprint(const char *str) {
	struct timespec req;
	req.tv_sec=0;
	req.tv_nsec=100e6;
	int i;
	
	for(i=0;str[i];++i) {
		fputc(str[i],stderr);
		nanosleep(&req,NULL);
	}
}
