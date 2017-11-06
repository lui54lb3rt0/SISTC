#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int main() {
    
    int r, status;
    r = fork();
    //executado pelo filho
    if(r==0) {
        printf("pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(4);
        printf("pid = %d, ppid = %d\n", getpid(), getppid());   //ESTE PRINT É FEITO DEPOIS DE O PAI TER TERINADO
    }
    
    sleep(1);   // PARA GARANTIR QUE O PAI AINDA ESTÁ A CORRER ENQUANTO O FILHO ESTÁ A IMPRMIR O PRIMEIRO PRINTF
    
//
}
    
