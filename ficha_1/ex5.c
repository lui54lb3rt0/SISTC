//ex5.c:
#include <stdio.h>
#include <unistd.h>
int mod(int p1, int p2) {
	int r = p1 % p2;
	return r;
}
int division(int p1, int p2) {
	int d = p1 / p2;
	return d;
}

int main() {
	int a;
	int b;
	while(1){
		scanf("%d", &a);
		scanf("%d", &b);
		if (a!=0){
			int d=division(a, b);
			int m=mod(a, b);
			printf("a: %d, b: %d, divisão: %d, resto: %d\n", a, b,d,m);
		}
		else{
			printf("ERRO!!\n\n");
			break;
		}
	}
	
}
