//ex6.c:
#include <stdio.h>
#include <unistd.h>

void minha_divisao(int dividendo, int divisor, int *ptr_quociente, int *ptr_resto){
    *ptr_quociente=dividendo/divisor;
    *ptr_resto=dividendo%divisor;
}

int main(int argc, char *argv[]){
	int a;
	int b;
    int flag;
    int d = 0;
    int r = 0;
	while(1){
        if(argc == 3){
            flag = 0;
            a = atoi(argv[1]);
            b = atoi(argv[2]);
        }else{
            flag = 1;
            scanf("%d", &a);
            scanf("%d", &b);
        }
		if (a != 0) {
            minha_divisao(a, b, &d, &r);
			printf("a: %d, b: %d, divisão: %d, resto: %d\n", a, b,d,r);
            if (flag == 0) break; 
		}
		else{
			printf("ERRO!!\n\n");
			break;
		}
	}
	
}