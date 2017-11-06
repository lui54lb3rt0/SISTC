//ex3.c:
#include <stdio.h>
#include <unistd.h>
void main(){
	char a = 46;
	char *ptr;
	ptr = &a;
	*ptr = 47;
	a = 48;
	printf("%d, %d\n", *ptr, a);
	a = '0';
	printf("%d, %c, %x\n", a, a, a);
}
