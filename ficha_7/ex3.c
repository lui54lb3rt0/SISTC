#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "mymq.h"

void *tmain(void *p)
{
  mymq_t *ptr_mq = (mymq_t *) p;
  char buffer[1024];
  
  while(1)
  {
    int n = mymq_receive(ptr_mq, buffer, 1024);
    buffer[n] = 0;
    printf("Received data: %s\n", buffer);
    sleep(2);
  }
}

int main() {
  char buffer[1024];
  time_t currtime;
  pthread_t tid;
  mymq_t mq;
  
  mymq_init(&mq, 1024, 10);  
  
  
  pthread_create(&tid, NULL, tmain, &mq);
  
  while(1) {
    sleep(1);
    currtime = time(NULL);
    ctime_r(&currtime, buffer);
    mymq_send(&mq, buffer, strlen(buffer));     
    printf("Sent data: %s", buffer);
  }
}



