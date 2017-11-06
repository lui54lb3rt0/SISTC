//ex5b.c:
#include <stdio.h>
#include <unistd.h>

void minha_divisao(int dividendo, int divisor, int *ptr_quociente, int *ptr_resto){
    *ptr_quociente=dividendo/divisor;
    *ptr_resto=dividendo%divisor;
}

int main() {
	int a;
	int b;
    int d=0;
    int r=0;
	while(1){
		scanf("%d", &a);
		scanf("%d", &b);
		if (a!=0){
            minha_divisao(a, b, &d, &r);
			printf("a: %d, b: %d, divisão: %d, resto: %d\n", a, b,d,r);
		}
		else{
			printf("ERRO!!\n\n");
			break;
		}
	}
	
}

