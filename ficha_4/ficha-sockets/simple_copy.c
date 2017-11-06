#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* const argv[]) {
  char buf[4096];
  
  FILE *fp1 = fopen(argv[1], "r");
  if(fp1 == NULL) {
    perror("fopen");
    exit(1);
  }

  FILE *fp2 = fopen("file.bin", "w");
  if(fp1 == NULL) {
    perror("fopen");
    exit(1);
  }
  
  while(1) {
    //read at most sizeof(buf) bytes from fp1 into buf
    int n = fread(buf, 1, sizeof(buf), fp1);
    if(n == 0)
      break;
      
    //write n bytes contained in buf into fp2 
    fwrite(buf, 1, n, fp2);
  }
  
  return 0;
}
