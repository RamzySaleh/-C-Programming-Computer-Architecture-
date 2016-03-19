
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv){

  int number;

  if (argc == 1){
    printf("error\n");
    return 0;
  }

  number = atoi(argv[1]);
  
  if (number%2 == 1){
    printf("odd\n");
  }
  else {
    printf("even\n");
  }
  return 0; 

}
