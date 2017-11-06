#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void recv_server_reply1(int);
void recv_server_reply2(int);

int my_connect_to_server(struct addrinfo *addr) {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  if (s == -1)
  {
    perror("socket");  
    exit(1);
  }
  
  if (connect(s, addr->ai_addr, addr->ai_addrlen) == -1)
  {
    perror("connect");  
    close(s);
    exit(2);
  }
  return s;
}

int main (int argc, char* const argv[]) {

  if(argc!=3) {
    printf("Usage: %s server_ip_address port_number\n",argv[0]);
    exit(1); 
  }
  
  struct addrinfo hints;
  struct addrinfo *addrs;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;          /* Any protocol */
  int r = getaddrinfo(argv[1], argv[2], &hints, &addrs);
  if (r != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
    exit(0);
  }



  
  //read a string
  char buf[4096];  
  printf("Enter a string: ");
  fgets(buf, sizeof(buf), stdin);
  
  //connect to server
  int s = my_connect_to_server(addrs);
  
  
  //send string to server
  write(s, buf, strlen(buf));
  
 
  recv_server_reply1(s);
  //recv_server_reply2(s);
  
  return 0;
}

 //version 1 - prints server reply as it receives it (by parts)
void recv_server_reply1(int s) 
{
  char buf[4096];

  printf("Reply from server: ");
  while(1) 
  {
    int n = read(s, buf, sizeof(buf)-1);
    if(n==0)
      break;
    buf[n] = 0;//terminate string (read does not do this)    
    fputs(buf, stdout);
    fflush(stdout);
  }
  

  printf("\n\n");
}

//version 2 - receives whole answer and then prints it  
void recv_server_reply2(int s) 
{
  char buf[4096];
  
  int bytes_recv = 0;
  while(1) 
  {
    int n = read(s, buf + bytes_recv, sizeof(buf) - 1 - bytes_recv);
    if(n==0)
      break;

    bytes_recv += n;
  }
  
  buf[bytes_recv] = 0;//terminate string (read does not do this)
  printf("Reply from server: %s\n\n", buf);
}
