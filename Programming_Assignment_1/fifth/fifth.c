#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main(int argc,char **argv){

  FILE *fileptr;
  int m; /* number of rows */
  int n; /* number of columns */
  int i; /* for reading */
  int j; /* for reading */
  int c; /*iterator for size*/
  int **arrOne;
  int **arrTwo;
  int **arrSum;

  if (argc == 1){
    printf("error\n");
    return 0;
  }
  
  fileptr = fopen(argv[1],"r");

  if (fileptr == NULL){
    printf("error\n");
    return 0;
  }
  
  
  fscanf(fileptr, "%d %d", &m, &n);

  arrOne = malloc(m*sizeof(int*));
  arrTwo = malloc(m*sizeof(int*));
  arrSum = malloc(m*sizeof(int*));
  
  for(c = 0; c < n; c++){
    arrOne[c] = malloc(n*sizeof(int));
    arrTwo[c] = malloc(n*sizeof(int));
    arrSum[c] = malloc(n*sizeof(int));
  }

  /* read array 1*/
  for(i = 0; i<m; i++){
    for (j = 0; j<n; j++){
      fscanf(fileptr, "%d", &arrOne[i][j]);
    }
  }

  /*read array 2*/
  for(i = 0; i<m; i++){
    for (j = 0; j<n; j++){
      fscanf(fileptr, "%d", &arrTwo[i][j]);
    }
  }

  /* summing */
  for(i = 0; i<m; i++){
    for (j = 0; j<n; j++){
      arrSum[i][j] = arrOne[i][j] + arrTwo[i][j];
    }
  }

  /* printing */
  for(i = 0; i<m; i++){
    for (j = 0; j<n; j++){
      printf("%d\t", arrSum[i][j]);
    }
    printf("\n");
  }
}
