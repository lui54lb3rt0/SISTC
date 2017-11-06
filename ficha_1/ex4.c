//ex4.c:
#include <stdio.h>
#include <unistd.h>
void teste(char p1, char p2, char *p3) {
	p2 = p2 + p1;
	*p3 = 3*p2;
}

int main() {
	char a = 10;
	char b = 20;
	teste(10, a, &b);
	printf("%d, %d\n", a, b);
}
