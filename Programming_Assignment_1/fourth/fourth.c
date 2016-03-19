#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


void insert(int value, char output[1000][15], int hashTable[], int i){

  int modValue = value%10000;
  
  if(hashTable[modValue] == -550){
    hashTable[modValue] = value;
    /*printf("value inserted:%d\n", value);*/
    strcpy(output[i], "inserted");
    return;
  } else if (hashTable[modValue] == value){
    /*printf("value duplicate:%d\n", value);*/
    strcpy(output[i], "duplicate");
    return;
  }
  while (hashTable[modValue]!= -550){
    if(hashTable[modValue] == value){
      /*printf("value duplicate:%d\n", value);*/
      strcpy(output[i], "duplicate");
      return;
    }
    modValue++;
  }
  hashTable[modValue] = value;
  /*printf("value inserted:%d\n", value);*/
  strcpy(output[i], "inserted");
  
}

void search(int value, char output[1000][15], int hashTable[], int i){
  int modValue = value%10000;

  if(hashTable[modValue] == -550){
    /*printf("value absent:%d\n", value);*/
    strcpy(output[i], "absent");
    return;
  } else if (hashTable[modValue] == value){
    /*printf("value present:%d\n", value);*/
    strcpy(output[i], "present");
    return;
  }

  while (hashTable[modValue]!= -550){
    if(hashTable[modValue] == value){
      /*printf("value present:%d\n", value);*/
      strcpy(output[i], "present");
      return;
    }
    modValue++;
  }
  /*printf("value absent:%d\n", value);*/
  strcpy(output[i], "absent");  
  return;
}



int main(int argc,char **argv){

  FILE *fileptr;
  char *instructions = malloc(1000);
  int* numbers = calloc(1000, sizeof(int));
  int* hashTable = malloc(10000*sizeof(int));
  char letteri = 'i';
  char letters = 's';
  int linenumber = 0;
  int i;
  char output[1000][15];
  char line[256];
  int validScanF = 0;
  char tempchar;
  int tempInt = 0;
  
  if (argc == 1){
    printf("error\n");
    return 0;
  }
  
  fileptr = fopen(argv[1],"r");

  if (fileptr == NULL){
    printf("error\n");
  }

  for(i = 0; i<500; i++){
    strcpy(output[i], "incorrect");
  }

  for(i = 0; i<10000; i++){
    hashTable[i] = -550;
  }

  while(fgets(line, sizeof(line), fileptr)!= NULL){
    validScanF = sscanf(line, " %c %d ", &tempchar, &tempInt);
    if (validScanF == 2){
      /* printf("read correct: ins num %c %d\n", tempchar, tempInt);*/
      instructions[linenumber] = tempchar;
      numbers[linenumber] = tempInt;
    }
    else {
      strcpy(output[linenumber], "error");
    }
    linenumber++;
  }

  for(i = 0; i<linenumber; i++){
    
    if (strcmp(output[i], "error")==0){
      continue;
    }
    else if (instructions[i] == letteri){
      /* printf("output before insert: %s\n", output[i]);*/
      insert(numbers[i], output, hashTable, i);
      /* printf("output after insert: %s\n", output[i]);*/
    }
    else if (instructions[i] == letters){
      /*printf("output before search: %s\n", output[i]);*/
      search(numbers[i], output, hashTable, i);
      /*printf("output after search: %s\n", output[i]);*/
    }
    else {
      strcpy(output[i], "error");
    }
  }
    
  if (linenumber == 0){
     printf("\n");
  } else {
      for (i = 0; i<linenumber; i++){
	printf("%s\n", output[i]);
      }
   }

  fclose(fileptr);  
  return 0;

  
}
