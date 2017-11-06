#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

    if(argc!=4) {
        printf("Usage: %s server_ip_address port_number filename\n",argv[0]);
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

    char buf[4096];
    FILE *fp1 = fopen(argv[3], "r");
    if(fp1 == NULL) {
        perror("fopen");
        exit(1);
    }


    //connect to server
    int s = my_connect_to_server(addrs);

    while(1) {
        //read at most sizeof(buf) bytes from fp1 into buf
        int n = fread(buf, 1, sizeof(buf), fp1);
        if(n == 0)
            break;

        write(s, buf, strlen(buf));

    }
    fclose(fp1);
    return 0;
}
