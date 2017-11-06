/*

        Developed by 1101420@ISEP 2017

*/

#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define VEHIC_MAXPLEN 81
typedef struct {
    char plate[6];
    char owner[VEHIC_MAXPLEN];
    double value;
} vehic_t;

void vehic_read(vehic_t *v);
void vehic_print(vehic_t *v);
int vehic_menu();
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

char http_header [] = 
"POST /dev/SISTC/vehicle.php HTTP/1.1\r\n\
Host: localhost\r\n\
Content-Type: application/x-www-form-urlencoded\r\n\
Content-Length: ";

char http_msg1[] = "GET /dev/SISTC/vehicles_v2.php?o=JSON HTTP/1.1\r\n\
Host: localhost\r\n\r\n";

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

    
    int op;
    vehic_t v;
    char buffer[4096];

    while(1) {
        op = vehic_menu();
        switch(op) {
            case 0: exit(1);
            case 1:
                vehic_read(&v);
                char content [256];
                char http_send [4096];

                sprintf(content, "plate=%.6s&owner=%s&value=%.2lf", v.plate, v.owner, v.value);
                sprintf(http_send,"%s%d\r\n\r\n%s\r\n", http_header, (int)strlen(content), content);
                int s = my_connect_to_server(addrs);
                write(s, http_send, strlen(http_send));
                printf("%s",http_send);
                //send new record to server
                recv_server_reply1(s);
                break;
                
            case 2:
                s = my_connect_to_server(addrs);
                write(s, http_msg1, strlen(http_msg1));
                recv_server_reply2(s);
                break;
        }
    }
    return 0;
}


void recv_server_reply1(int s) 
{
    char buf[4096];
    char *ptr,*ptr2;

    while(1) 
    {
        int n = read(s, buf, sizeof(buf)-1);
        if(n==0)
            break;
        buf[n] = 0;//terminate string (read does not do this)
        //para DEBUG descomentar 2 linhas abaixo
//        fputs(buf, stdout);
//        fflush(stdout);
    }

    //procura a tag <ws-error>
    if( (ptr = strstr(buf, "<ws-error>"))!=NULL)
    {
        //ptr fica a apontar para o primeiro carácter da mensagem de erro
        ptr = strstr(ptr,">") + 1;
        //função strsep substitui o ‘<’ de “</ws-error>” pelo fim de string
        ptr2 = ptr;
        ptr = strsep(&ptr2, "<");
        printf("Error message from server: \"%s\"\n\n", ptr);
    }
    else
    {
        printf("OK\n");
    }

}

void recv_server_reply2(int s) 
{
    char buffer[4096];
    int n;
    char c; //contains received character
    vehic_t v;
    char buffer2[256];
    int nchars, state = 0;
    
    while((n = read(s, buffer, sizeof(buffer)-1))>0) {
        buffer[n] = 0;
//        fputs(buffer, stdout);
        
        for (int i = 0; i < strlen(buffer); i++)
        {
            c= buffer[i];
            switch(state) {
                case 0:
                case 2:
                case 4:
                    if( c == '"' ) { //found opening "
                        state++;
                        nchars = 0;
                        break;
                    }
                    if( c == '[' && state != 0 ) { //new record before completing current one
                        printf("invalid record\n");
                        state = 0;
                        break;
                    }
                    break;
                case 1://reading plate
                    if( c == '"' ) { //found closing "
                        state = 2;
                        break;
                    }
                    if( nchars == 6 ) //discard unexpected chars
                        break;
                    v.plate[nchars++] = c;
                    break;
                case 3://reading owner
                    if( c == '"' ) { //found closing "
                        state = 4;
                        v.owner[nchars] = 0;
                        break;
                    }
                    if( nchars == VEHIC_MAXPLEN-1 ) //discard unexpected chars
                        break;
                    v.owner[nchars++] = c;
                    break;
                case 5://reading value
                    if( c == '"' ) { //found closing "
                        state = 0;
                        buffer2[nchars] = 0;
                        v.value = atof(buffer2);
                        vehic_print(&v);
                        break;
                    }
                    if( nchars == sizeof(buffer2)-1 ) //discard unexpected chars
                        break;
                    buffer2[nchars++] = c;
                    break;
            }
        }
    }
}

int vehic_menu() { 
    int op; 
    printf("\n0 - Exit\n"); 
    printf("1 - Insert new record\n"); 
    printf("2 - Print all\n"); 
    printf("\nEnter option: "); 
    fflush(stdout);
    scanf("%d", &op); 
    getchar(); //consume '\n'
    printf("\n");

    return op; 
}

void vehic_read(vehic_t *v) {
    char buf[VEHIC_MAXPLEN];

    printf("Plate (6 characters): ");
    fgets(buf, VEHIC_MAXPLEN, stdin);
    memcpy(v->plate, buf, 6);
    printf("Owner: ");
    fgets(v->owner, VEHIC_MAXPLEN, stdin);
    v->owner[strlen(v->owner)-1] = 0; //"move" the end of the string to the place of '\n'
    printf("Value: ");
    scanf("%lf", &v->value);
    getchar(); //consume \n
}

void vehic_print(vehic_t *v) {
    v->owner[VEHIC_MAXPLEN-1] = 0;//double check
    printf("%.6s - %s - %.2lf\n", v->plate, v->owner, v->value);
}