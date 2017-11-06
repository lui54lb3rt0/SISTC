#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void myhandler(int signum);
void print_pending();

int main() 
{
  int r;  
  struct sigaction act;
  sigset_t new_mask;


  //bloquear todos os sinais menos o SIGTERM e o SIGQUIT
  sigfillset(&new_mask);
  sigdelset(&new_mask, SIGTERM);
  sigdelset(&new_mask, SIGQUIT);
  if( sigprocmask(SIG_SETMASK, &new_mask, NULL) == -1)
  {
    perror("sigprocmask");
    exit(1);
  };


  act.sa_handler = myhandler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  if(sigaction(SIGTERM, &act, NULL)==-1)
  {
    perror("sigaction");
    exit(1);
  };
  if(sigaction(SIGQUIT, &act, NULL)==-1)
  {
    perror("sigaction");
    exit(1);
  };


  while(1){
    printf("Ola! Sou o processo %d. Mas pode confirmar com o comando ps.\n", getpid());
    print_pending();
    r = sleep(10);
    if(r>0)
      printf("Sleep terminou %d segundos antes do instante esperado\n", r);
  }
         
  return 0;
}

void myhandler(int signum)
{
  printf("Recebi o sinal %d (%s). Mas nao quero terminar!\n", signum, strsignal(signum));
  sleep(3); // se enviar o mesmo sinal novamente nesta altura ele ficará bloqueado até que a função myhandler termine. O que acontece se enviar o SIGTERM e logo de seguida o SIGQUIT?
  printf("Fim de myhandler (%d)\n", signum);
}

void print_pending()
{
  int signum;
  sigset_t set;

  sigpending(&set);

  for(signum = 1; signum < NSIG; ++signum)
    if(sigismember(&set, signum))
      printf("Sinal %d (%s) pendente\n", signum, strsignal(signum));
}

