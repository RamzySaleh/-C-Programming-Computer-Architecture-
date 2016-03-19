#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct node_ll {
  int *x;
  struct node_ll *next;
};
  

void addNode(int value, struct node_ll **root){

  struct node_ll* currentptr;
  struct node_ll* prevptr = NULL;
  struct node_ll* newNode;
  /*printf("here\n");*/
  if(*root == NULL){
   newNode = (struct node_ll *) malloc(sizeof(struct node_ll));
   newNode->next = NULL;
   newNode->x = (int*) malloc(sizeof(int));
   *(newNode->x)=value;
   free(*root);
   *root = newNode;
   return;
  }
  /*printf("here 2\n");*/
  if((*root)->x == NULL){
    /*printf("here 2a\n");*/
    (*root)->x = (int*) malloc(sizeof(int));
    /*printf("root's x %d\n", *((*root)->x));*/
    *((*root)->x) = value;
    /*printf("seg fault test 2a\n");*/
    return;
  }
  if(*((*root)->x) == value){
    /*printf("here 2b\n");*/
    return;
  }
  /*printf("here 3\n");*/
  newNode = (struct node_ll *) malloc(sizeof(struct node_ll));
  newNode->x = (int*) malloc(sizeof(int));
  *(newNode->x) = value;
  newNode->next = NULL;

  if (value < *((*root)->x)){
    newNode->next = (*root);
    (*root) = newNode;
    return;
  }
  /*printf("here 4\n");*/
  prevptr = (*root);
  currentptr = (*root)->next;
  /*printf("here 4a\n");*/
  if ((*root)->next == NULL){
     prevptr->next = newNode;
    return;
  }
  while(currentptr != NULL && value > *(currentptr->x)){
    /* printf("currentptr add loop: %d\n",*(currentptr->x));*/
    prevptr = currentptr;
    currentptr = currentptr->next;
  }
  /* printf("here 5\n");*/
  if (currentptr == NULL){
    prevptr->next = newNode;
    return;
  }
  /* printf("here 6\n");*/
  if (*(prevptr->x) == value){
    return;
  } else if (*(currentptr->x) == value){
    return;
  }
  /* printf("here 7\n");*/
  newNode->next = currentptr;
  prevptr->next = newNode;
  return;
  

}

void printLL(struct node_ll **root){

  struct node_ll *currentptr = *root;
  if ((*root) == NULL || (*root)->x == NULL){
    printf("\n");
    return;
  }

  while (currentptr != NULL && currentptr->next != NULL){
    printf("%d\t", *(currentptr->x));
    currentptr = currentptr->next;
  }

  printf("%d\n", *(currentptr->x));

}


void deleteNode(int value, struct node_ll **root){

  struct node_ll * nextTemp = NULL;
  struct node_ll * prevptr = NULL;
  struct node_ll * currentptr = *root;

  /* this is if root is to be deleted
     if the root doesn't have a next, it will set its x pointer to null
     if it does have a next, root is free and the new root is the next node.
  */
  /* printf("delete 1\n");*/
  if(*((*root)->x) == value){

    if((*root)->next == NULL){
      (*root)->x = 0;
      return;
    } else {
      nextTemp = (*root)->next;
      *root = nextTemp;
      return;
    }
  }
  /* printf("delete 2\n");*/
  if((*root)->next == NULL){
    return;
  }
  /* printf("delete 3\n");*/
  while(*(currentptr->x) != value){
    if (currentptr->next == NULL){
      return;
    }
    prevptr = currentptr; 
    currentptr = currentptr->next;
  }
  /* printf("delete 4\n");*/
  nextTemp = currentptr->next;
  prevptr->next = nextTemp;
  /* printf("delete 5\n");*/
}

int main(int argc,char **argv){

  FILE *fileptr;
  int linenumber = 0;
  int validScanF = 0;
  int tempInt = 0;
  int j=0;
  char tempchar;
  char *instructions = malloc(500);
  char line[256];
  char letteri = 'i';
  char letterd = 'd';
  int* numbers = calloc(500, sizeof(int));
  struct node_ll *root = (struct node_ll *) malloc(sizeof(struct node_ll));
  root->next = NULL;
  root->x = NULL;
  
  if (argc == 1){
    printf("error\n");
    return 0;
  }

  fileptr = fopen(argv[1],"r");

  if (fileptr == NULL){
    printf("error\n");
    return 0;
  }
  
  
  while(fgets(line, sizeof(line), fileptr)!=NULL){
    validScanF = sscanf(line, " %c %d ", &tempchar, &tempInt);
    /* printf("%c %d\n", tempchar, tempInt);
       printf("line number: %d\n",linenumber);*/
    if (validScanF == 2){
      instructions[linenumber] = tempchar;
      numbers[linenumber] = tempInt;
      /* printf("L158\n");*/
    }
    else {
     printf("error\n");
     return 0;
    }
    linenumber++;
  }
  
  /* printf("line number end: %d\n",linenumber); */
  
  while(j<linenumber){
    /*printf("j = %d\n",j);*/
    if (instructions[j] == letteri){
      /*
      printf("before add \n");
      printf("insturctions[j] numbers[j]%c%d\n", instructions[j], numbers[j]);
      */
      addNode(numbers[j], &root);
      /* printf("after add\n");*/
    }
    else if (instructions[j] == letterd){
      deleteNode(numbers[j], &root);
    } else {
      printf("error\n");
      return 0;
    }
    j++;
  }
   
  printLL(&root);
  fclose(fileptr);
  return 0;
}
