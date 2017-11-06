#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h> //inet_ntoa



int prepara_socket_servidor(int port);


int main(int argc, char *argv[]){
  int ns, s, n;
  unsigned int clilen;  
  struct sockaddr_in cli_addr;
  
  signal(SIGPIPE, SIG_IGN);
  signal(SIGCHLD, SIG_IGN);
    
  if(argc!=2) {
    printf("Usage: %s port_number\n", argv[0]);
    exit(1); 
  }
       
  s = prepara_socket_servidor(atoi(argv[1]));

  while(1) {
    char c;
    
    printf("Waiting connection\n");  
    clilen = sizeof(cli_addr); 
    ns = accept(s, (struct sockaddr *) &cli_addr, &clilen);
    pid_t r = fork();
    if (r == 0){

        printf("Connection from %s\n", inet_ntoa(*((struct in_addr *) &(cli_addr.sin_addr) )));


        //serve request (communication with the client)
        while(1)
        {
          n = read(ns, &c, 1);
          if(c=='\n' || n==0)//read until it detects a newline ('\n') or end of data stream
            break;

          c = toupper(c);

          usleep(100000);
          write(ns, &c, 1);
        }
        
        close(ns);
        exit(1);
    }
    close(ns);
  }
  
  return 0;
}

int prepara_socket_servidor(int port)
{
  int s;
  struct sockaddr_in serv_addr;

  s = socket(PF_INET, SOCK_STREAM, 0);
  if(s < 0){
    perror("socket");
    exit(1);
  }
        
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);
  
  if(bind(s, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
    perror("bind");
    exit(1);
  }    
  
  listen(s, 5); 

  return s;
}

