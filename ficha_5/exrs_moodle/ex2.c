#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void myhandler(int signum);

int main() {
  int r;
  struct sigaction act;


  act.sa_handler=myhandler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  if(sigaction(SIGTERM, &act, NULL)==-1)
  {
    perror("sigaction");
    exit(1);
  };

  
  while(1){
    printf("Ola! Sou o processo %d. Mas pode confirmar com o comando ps.\n", getpid());
    r = sleep(10);
    if(r>0)
      printf("Sleep terminou %d segundos antes do instante esperado\n", r);
  }
         
  return 0;
}

void myhandler(int signum)
{
  printf("Recebi o sinal %d (%s). Mas nao quero terminar!\n", signum, strsignal(signum));
}
