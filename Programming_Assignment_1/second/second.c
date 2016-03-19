
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv){

  int number;
  int i;
  
  if (argc == 1){
    printf("error\n");
    return 0;
  }

  number = atoi(argv[1]);

  for (i = 2; i < number; i++){
    if (number%i == 0){
      printf("no\n");
      return 0;
    }
  }
  printf("yes\n");
  return 0;
  
}
