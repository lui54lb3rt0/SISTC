#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char http_msg1[] = "GET /dev/SISTC/vehicles_v2.php?o=JSON HTTP/1.1\r\n\
Host: localhost\r\n\r\n";


int main (int argc, char* const argv[]) {
  
  char server[] = "localhost";
  char port[] = "80";
  
  //Obtenção do endereço do servidor (basta fazer isto uma vez, mesmo que haja várias ligações)  
  struct addrinfo hints;
  struct addrinfo *result;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0; //Any protocol
  hints.ai_flags = 0;  
  int r = getaddrinfo(server, port, &hints, &result);
  if (r != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
    exit(0);
  }
    
    
  int s = socket(AF_INET, SOCK_STREAM, 0);
  if (s == -1){  
    perror("connect");
    exit(1);
  }

  if (connect(s, result->ai_addr, result->ai_addrlen) == -1){  
    perror("connect");
    exit(1);
  }
    
  char buffer[4096];
  

  write(s, http_msg1, strlen(http_msg1));
  int n;
  while((n = read(s, buffer, sizeof(buffer)-1))>0) {
    buffer[n] = 0;
    fputs(buffer, stdout);
  }
 
  return 0;
}
