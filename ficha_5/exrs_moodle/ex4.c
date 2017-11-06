#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void myhandler(int signum);
void print_pending();

int main() 
{
  int r;    
  struct sigaction act;
  sigset_t new_mask;


  //bloquear todos os sinais menos o SIGTERM, o SIGINT, o SIGTSTP e o SIQUIT
  sigfillset(&new_mask);
  sigdelset(&new_mask, SIGTERM);
  sigdelset(&new_mask, SIGINT);
  sigdelset(&new_mask, SIGTSTP);
  sigdelset(&new_mask, SIGQUIT);
  if( sigprocmask(SIG_SETMASK, &new_mask, NULL) == -1)
  {
    perror("sigprocmask");
    exit(1);
  };


  //ignorar o SIGINT
  if(signal(SIGINT, SIG_IGN)==SIG_ERR)//ctrl+c
  {
    perror("signal");
    exit(1);
  };

   
  //estabelecer o handler para os sinais SIGTERM, SIGQUIT, SIGTSTP
  act.sa_handler = myhandler;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_NODEFER;//handler será interrompido caso receba o sinal durante a sua execução (sem esta flag, o sinal é bloqueado temporariamente).
  if(sigaction(SIGTERM, &act, NULL)==-1)//kill pid
  {
    perror("sigaction");
    exit(1);
  };
  if(sigaction(SIGQUIT, &act, NULL)==-1)//"ctrl+\"
  {
    perror("sigaction");
    exit(1);
  };
  if(sigaction(SIGTSTP, &act, NULL)==-1)//ctrl+z
  {
    perror("sigaction");
    exit(1);
  };

  time_t t0 = time(NULL);
  while(1){
    printf("Ola! Passaram %ld segundos desde o arranque do programa. Execute o comando \"ps -u\" noutra consola para descobrir o meu PID.\n", time(NULL)-t0);
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
  sleep(3); // se enviar o mesmo sinal novamente nesta altura, a função myhandler será chamada novamente
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

