#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int nc, nt;
void cld_handler(int);
void int_handler(int);

int main(int argc, char *argv[]) {
  pid_t r;
  sigset_t ss1;
  int block_sigchld = 0;
  if(argc>1 && argv[1][0]=='b')
    block_sigchld = 1;
    
  sigemptyset(&ss1);
  sigaddset(&ss1, SIGCHLD);

  signal(SIGCHLD, cld_handler);
  
  nt = 0;
  for( nc = 0; nc < 100; ++nc) {

    //CREATE NEW PROCESS
    r = fork();
    if( r == 0 ) {
      //TERMINATE NEW PROCESS
      sleep(5); //Comment this line and observe that some messages will be printed twice.
                //That happens because SIGCHLD will sometimes interrupt the printf function
      exit(1);
    }

    //JUST IN CASE THE SYSTEM IS UNABLE TO CREATE NEW PROCESSES
    if( r == -1)
    {
      perror("fork");
      abort();
    }

    if(block_sigchld) sigprocmask(SIG_BLOCK, &ss1, NULL);
    printf("Created process %d (PID = %d)\n", nc+1, r);
    sigprocmask(SIG_UNBLOCK, &ss1, NULL);
    

  }
  
  if(block_sigchld)  sigprocmask(SIG_BLOCK, &ss1, NULL);
  printf("All processes created ============================\n");
  sigprocmask(SIG_UNBLOCK, &ss1, NULL);
  
  signal(SIGINT, int_handler);
  while(1) {
    pause();

    if(block_sigchld) sigprocmask(SIG_BLOCK, &ss1, NULL);
    printf("Ouch!!!\n");
    sigprocmask(SIG_UNBLOCK, &ss1, NULL);
  }
  
  return 0;
};

void cld_handler(int signum){
  pid_t p;
  int wstatus;
  
	while(  (p = waitpid(-1, &wstatus, WNOHANG)) > 0) {
	  ++nt;
	  printf("CLD handler: Process terminated (PID = %d). %d processes remaining. ", p, nc - nt);
	  if(WIFSIGNALED(wstatus))
	    printf("Terminated by signal %d\n",  WTERMSIG(wstatus));
	  else
	    printf("\n");
	}

}

void int_handler(int signum){
  pid_t p;
  int wstatus;
  
  printf("Entering INT handler. ");
  while(  (p = waitpid(-1, &wstatus, WNOHANG)) > 0) {
    ++nt;
    printf("INT handler: Process terminated (PID = %d). %d processes remaining. ", p, nc - nt);
    if(WIFSIGNALED(wstatus))
      printf("Terminated by signal %d\n",  WTERMSIG(wstatus));
    else
      printf("\n");

  }
  exit(0);
}
