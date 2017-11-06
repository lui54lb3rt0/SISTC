#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void simula_processamento();
int main() {
    int r, i, status;
    r = fork();
    printf("pid = %d, ppid = %d\n", getpid(), getppid());
    sleep(1);
    srandom(getpid());//
        if(r==0) {
            for(i=0; i<20; ++i) {
                simula_processamento();
                printf("%d ", i);
                fflush(stdout);
            }
        }
        exit(1);

    for(i=20; i<40; ++i) {
        simula_processamento();
        printf("%d ", i);
        fflush(stdout);
    }
    r = wait(&status); //aguarda que processo filho termine
    printf("\n");
    if(WIFEXITED(status))
        printf("Valor de retorno de (%d): %d\n", r, WEXITSTATUS(status));
    else
        printf("Filho (%d) terminou de forma anormal\n", r);
        return 0;
}
    
#define NELEM 64

void simula_processamento() {
    int i,j;
    double d1[NELEM];
    for(i=0;i<random();++i) {
        for(j=0;j<NELEM;++j)
            d1[j]=d1[j]*1.1;
    }
}