#include <netinet/in.h>
#include <unistd.h> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
//inet_ntoa
#include <arpa/inet.h>

void atende_pedido(int);
int prepara_socket_servidor(int port);

int main(int argc, char *argv[]){
  int ns, s;
  unsigned int clilen;  
  struct sockaddr_in cli_addr;

  if(argc!=2) {
    printf("Usage: %s port_number\n",argv[0]);
    exit(1); 
  }
     
  signal(SIGPIPE, SIG_IGN);
  
  s = prepara_socket_servidor(atoi(argv[1]));

  clilen = sizeof(cli_addr); 
  while(1) {
    printf("Waiting connection\n");  
    ns = accept(s, (struct sockaddr *) &cli_addr, &clilen);  
    printf("Connection from %s\n", inet_ntoa(*((struct in_addr *) &(cli_addr.sin_addr) )));
  
    atende_pedido(ns);
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


char http_header1[] =
"HTTP/1.1 200 OK\r\n\
Server: SISTC Dummy Web Server\r\n\
Content-Type: text/html\r\n\
Content-Length:";

char http_header2[] = "Date:";
char http_header3[] = "Last-Modified:";

char html_str1_simple[] = 
"<!DOCTYPE html>\n\
<html>\n\
<head>\n\
  <title>SISTC - Servidor Web</title>\n\
  <meta charset=\"UTF-8\">\n\
</head>\n\
<body>\n\
O seu browser enviou-nos a seguinte mensagem HTTP a ";

char html_str1a_simple[] = " (UTC):<br><br>\n";

char html_str2_simple[] =  "</body>\n</html>\n";



char html_str1_css[] = 
"<!DOCTYPE html>\n\
<html>\n\
<head>\n\
  <title>SISTC - Servidor Web</title>\n\
  <meta charset=\"UTF-8\">\n\
  <style type=\"text/css\">\n\
    .mydiv\n\
    {\n\
      font-family: \"Courier New\", Courier, monospace;\n\
    }\n\
  </style>\n\
</head>\n\
<body>\n\
O seu browser enviou-nos a seguinte mensagem HTTP";

char html_str1a_css[]=
" (UTC):<br><br>\n\
<div class=\"mydiv\">\n";

char html_str2_css[] =  "</div></body>\n</html>\n";

char *html_str1 = html_str1_simple;
char *html_str1a = html_str1a_simple;
char *html_str2 = html_str2_simple;
//char *html_str1 = html_str1_css;
//char *html_str1a = html_str1a_css;
//char *html_str2 = html_str2_css;

void atende_pedido(int ns) {
  char buf1[40960];
  char *buf2 = malloc(1);
  buf2[0] = 0;//end of string
  int nbytes = 1;
  int n;
  FILE *fp = fdopen(ns, "r+");
  
  //add current date to html text
  time_t tim1 = time(NULL);
  char *gmt_time = asctime(gmtime(&tim1));
  gmt_time[strlen(gmt_time)-1] = 0;//asctime returns a string terminated in '\n'
  nbytes += strlen(gmt_time)+strlen(html_str1a);
  buf2 = realloc(buf2, nbytes);
  sprintf(buf2, "%s%s", gmt_time, html_str1a);

  
  while( fgets(buf1,sizeof(buf1),fp)!=NULL )
  {
    n = strlen(buf1); 
    //end of HTTP request is detected by an empty line ("\r\n")
    if(n<=2)
      break;
      
    buf1[n-1]=0;
    buf1[n-2]=0;
    
    int nnbytes = nbytes + strlen(buf1)+5;
    buf2 = realloc(buf2, nnbytes);
    sprintf(buf2+nbytes-1,"%s<br>\n",buf1);
    nbytes = nnbytes;

    if(buf1[0]=='\n' || buf1[0]=='\r')
      break;
  } 

  //imprime no stdout (debug)
  //printf(buf2);
  
  fflush(fp);
  
  n = strlen(buf2);
  fprintf(fp, "%s %lu\r\n%s %s\r\n%s %s\r\n\r\n", 
    http_header1, strlen(html_str1)+strlen(html_str2) + n, 
    http_header2, gmt_time,
    http_header3, gmt_time);
  
  fputs(html_str1, fp);
  fputs(buf2, fp);
  fputs(html_str2,fp);
   
  fclose(fp);
  free(buf2);
}



