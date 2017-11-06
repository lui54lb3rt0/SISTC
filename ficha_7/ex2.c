#include <pthread.h>
#include <sys/types.h> 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

void myprint(const char *str);
void *myfunc(void *);
sem_t *psem;

int main()
{
	char *buf = (char *) mmap(NULL, 8, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_unlink("/sem1");			//para desbloquear o semaforo
	psem = sem_open("/sem1", O_CREAT | O_RDWR, 0600, 1);
	int r = fork();
	if(r==0){
		sprintf(buf,"%d: Ola -----------------------------------------\n",getpid());  
		myfunc(buf);

	} else {
//		sleep(1);
		sprintf(buf,"%d: Ole +++++++++++++++++++++++++++++++++++++++++\n",getpid());
		myfunc(buf);
		return(0);
	}

	return(0);
}

void *myfunc(void *arg){
	while(1) {
		sleep(1);
		sem_wait(psem); 
		myprint((char *)arg);
		sem_post(psem);
	}

}


