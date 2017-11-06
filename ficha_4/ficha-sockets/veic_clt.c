#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


#define VEHIC_MAXPLEN 81
typedef struct {
  char plate[6];
  char owner[VEHIC_MAXPLEN];
  double value;
} vehic_t;

void vehic_read(vehic_t *v);
void vehic_print(vehic_t *v);
int vehic_menu();


int main (int argc, char* const argv[]) {
  int op;

  vehic_t v;

  while(1) {
    op = vehic_menu();
    switch(op) {
    case 0: exit(1);
    case 1:
      vehic_read(&v);

      //send new record to server
      
      break;
    case 2:
      
      //call vehic_print for each record
      vehic_print(&v);

      break;
    } 
  }
   
  return 0;
}


//do not change code below!!

int vehic_menu() { 
  int op; 
  printf("\n0 - Exit\n"); 
  printf("1 - Insert new record\n"); 
  printf("2 - Print all\n"); 
  printf("\nEnter option: "); 
  fflush(stdout);
  scanf("%d", &op); 
  getchar(); //consume '\n'
  printf("\n");
  
  return op; 
}

void vehic_read(vehic_t *v) {
  char buf[VEHIC_MAXPLEN];
  
  printf("Plate (6 characters): ");
  fgets(buf, VEHIC_MAXPLEN, stdin);
  memcpy(v->plate, buf, 6);
  printf("Owner: ");
  fgets(v->owner, VEHIC_MAXPLEN, stdin);
  v->owner[strlen(v->owner)-1] = 0; //"move" the end of the string to the place of '\n'
  printf("Value: ");
  scanf("%lf", &v->value);
  getchar(); //consume \n
}

void vehic_print(vehic_t *v) {
  v->owner[VEHIC_MAXPLEN-1] = 0;//double check
  printf("%.6s - %s - %.2lf\n", v->plate, v->owner, v->value);
}
