#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int i = 0;


int main(){
    pid_t r = fork();
    if (r == 0){
        sleep(10);
        printf("%d: %d\n",getpid(),i);
        return 0;
    }
    
    i = i + 1;
    wait(NULL);
    printf("%d: %d\n",getpid(),i);
    return 0;
}