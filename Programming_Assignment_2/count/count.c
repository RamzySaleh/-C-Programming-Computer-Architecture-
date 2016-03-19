#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct node_ll {
  long int x;
  struct node_ll *next;
};

int insert(long int value, struct node_ll** hashTable){

  int modValue = value%1000;
  struct node_ll* n;
  struct node_ll* ptr;

  if(hashTable[modValue] == NULL){
    n = (struct node_ll*)malloc(sizeof(struct node_ll));
    n->x = value;
    hashTable[modValue] = n;
    return 1;
  } else {
    ptr = hashTable[modValue];
    while(ptr != NULL){
      if ((ptr->x) == value){
	return 0;
      }
      ptr = ptr->next;
    }
    ptr = hashTable[modValue];
    n = (struct node_ll*)malloc(sizeof(struct node_ll));
    n->x = value;
    n->next = ptr;
    hashTable[modValue] = n;
    return 1;
  }
  
}

int main(int argc,char **argv){

  FILE *fileptr;
  struct node_ll* hashTable[1000];
  long int uniqueValues = 0;
  long int hexToInsert;
  int i;
  int validScanF = 0;
  int duplicate = 0;
  char line[256];

  if (argc == 1){
    printf("error\n");
    return 0;
  }
  
  fileptr = fopen(argv[1],"r");

  if (fileptr == NULL){
    printf("error\n");
    return 0;
  }

  for(i = 0; i<1000; i++){
    hashTable[i] = NULL;
  }

  while(fgets(line, sizeof(line), fileptr)!= NULL){
    validScanF = sscanf(line, "%zx", &hexToInsert);
    if (validScanF == 1){
      duplicate = insert(hexToInsert, hashTable);
      if (duplicate != 0){
	uniqueValues ++;
      }
    }
  }
  printf("%ld\n", uniqueValues);
  fclose(fileptr);  
  return 0;
}
