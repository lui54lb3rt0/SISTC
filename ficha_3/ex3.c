#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int main() {
    char *ptr = malloc(8);
    int r, status;
    r = fork();
    strcpy(ptr,"pai");   
    //executado pelo filho
    if(r==0) {
        strcpy(ptr,"filho");
        printf("%s\n",ptr );
        exit(1);
    }
    r = waitpid(-1, &status, 0); //aguarda que processo filho termine
    
    printf("%s\n",ptr);

}
    
