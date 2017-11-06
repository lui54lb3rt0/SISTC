//ex7.c:
#include <stdio.h>
#include <unistd.h>

char *strcpy(char *dst, const char *src) {
	char *cp = dst;
	while (*cp++ = *src++);
	return dst;
}

void *memcpy(void *dst, const void *src, size_t n) {    //size_t <=> int
    char *s = (char *) src;
    char *end = s+n;
    char *d = (char *) dst;
    
    while (s != end)
        *d++ = *s++;
    return dst;
}

int main(int argc, char *argv[]){
    char *a;
    char str1[] = "Teste!";
    int data1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    char str2[1000];
    int data2[1000];
    strcpy(str2,str1); // ou a=strcpy(&str2[0],&str1[0]);
    printf( " %ld, %ld\n" , sizeof(str2), sizeof(str1));
    memcpy(data2,data1,sizeof(data1)); // ou a=strcpy(&str2[0],&str1[0]);
    printf( " %ld, %ld\n" , sizeof(data2), sizeof(data1));
/*
    ###################################
    # para controlo de erros          #
    ###################################

    if(strcpy(str2,str1) == NULL){
        printf("ERRO!!");    
    }
    
}
