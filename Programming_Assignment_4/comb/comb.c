#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct node {
  int val;
  char id;
  struct node *next;
};

int and(int op1, int op2){
  if (op1 == 1 && op2 == 1){
    return 1;
  } else {
    return 0;
  }
}

int and3(int op1, int op2, int op3){
  int op1ANDop2 = and(op1, op2);
  return and(op1ANDop2, op3);
}

int or(int op1, int op2){
  if (op1 == 1 || op2 == 1){
    return 1;
  } else {
    return 0;
  }
}
int not(int op1){
  if (op1 == 0){
    return 1;
  } else {
    return 0;
  }
}

int multi2(int i1, int i2, int s1){
  if(s1 == 0){
    return i1;
  } else {
    return i2;
  }
}

int multi4(int i1, int i2, int i3, int i4, int s1, int s2){
  if (s1 == 0 && s2 == 0){
    return i1;
  } else if (s1 == 0 && s2 == 1) {
    return i2;
  } else if (s1 == 1 && s2 == 1) {
    return i3;
  } else {
    return i4;
  }
}

int multi8(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int s1, int s2, int s3){
  if (s1 == 0 && s2 == 0 && s3 == 0){
    return i1;
  } else if (s1 == 0 && s2 == 0 && s3 == 1){
    return i2;
  } else if (s1 == 0 && s2 == 1 && s3 == 1){
    return i3;
  } else if (s1 == 0 && s2 == 1 && s3 == 0){
    return i4;
  } else if (s1 == 1 && s2 == 1 && s3 == 0){
    return i5;
  } else if (s1 == 1 && s2 == 1 && s3 == 1){
    return i6;
  } else if (s1 == 1 && s2 == 0 && s3 == 1){
    return i7;
  } else {
    return i8;
  }
}

int* decoder2(int i1, int i2){
  int i1NOT = not(i1);
  int i2NOT = not(i2);
  int *decode2Arr = malloc(4*sizeof(int));
  decode2Arr[0] = and(i1NOT, i2NOT);
  decode2Arr[1] = and(i1NOT, i2);
  decode2Arr[2] = and(i1, i2);
  decode2Arr[3] = and(i1, i2NOT);
  return decode2Arr;
}

int* decoder3(int i1, int i2, int i3){
  int i1NOT = not(i1);
  int i2NOT = not(i2);
  int i3NOT = not(i3);
  int *decode3Arr = malloc(8*sizeof(int));
  decode3Arr[0] = and3(i1NOT,i2NOT,i3NOT);
  decode3Arr[1] = and3(i1NOT,i2NOT,i3);
  decode3Arr[2] = and3(i1NOT,i2,i3);
  decode3Arr[3] = and3(i1NOT,i2,i3NOT);
  decode3Arr[4] = and3(i1,i2,i3NOT);
  decode3Arr[5] = and3(i1,i2,i3);
  decode3Arr[6] = and3(i1,i2NOT,i3);
  decode3Arr[7] = and3(i1,i2NOT,i3NOT); 
  return decode3Arr;
}

int find(struct node **inputLL, struct node **outputLL, struct node **intermediateLL, char findMe){

  struct node* ptr;

  if(findMe == '1' || findMe == '0'){
    return atoi(&findMe);
  }
  
  if(findMe >= 'a' && findMe <= 'z'){
    ptr = *intermediateLL;
    while (ptr!= NULL){
      if (ptr->id == findMe){
	return ptr->val;
      }
      ptr = ptr->next;
    }
  } else {
    ptr = *inputLL;
    while(ptr!=NULL){
      if(ptr->id == findMe){
	return ptr->val;
      }
      ptr = ptr->next;
    }
    ptr = *outputLL;
    while(ptr!=NULL){
      if(ptr->id == findMe){
	return ptr->val;
      }
      ptr = ptr->next;
    }
  }
  
  printf("not found");
  return -10;
}
    
int main(int argc,char **argv){
  FILE *fileptr;
  int i=0, numLines = 0, j,k,m,n, numCases=0, numInputs, numOutputs;
  int **inputValues;
  int *decoderTemp;
  char *p;
  char *command;
  char buff[256];
  char *test[512];
  char ***testToken;
  char i1, i2, i3, i4, i5, i6, i7, i8, s1, s2, s3;
  char o1, o2, o3, o4, o5, o6, o7, o8;
  char multiType, decoderType;
  int ii1,ii2, ii3, ii4, ii5, ii6, ii7, ii8, is1, is2, is3;
  struct node *outputhead;
  struct node *inputhead;
  struct node *intermediate;
  struct node *ptr;
  struct node *temp;
  struct node *newInter;
  

  if (argc <= 2){
    printf("error\n");
    return 0;
  }
  
  fileptr = fopen(argv[1],"r");

  if (fileptr == NULL){
    printf("error\n");
    return 0;
  }

  while(fgets(buff, sizeof(buff), fileptr) != NULL){
    test[i] =  strdup(buff);
    /*printf("test[%d] = %s\n",i,test[i]);*/
    i++;
    numLines++;
    /*printf("numLines: %d\n", numLines);*/
  }
  /*printf("\n");*/
  for(j=0; j<numLines; j++){
    /*printf("test[%d] = %s", j, test[j]);*/
  }
  /* printf("\n");*/
  fclose(fileptr);

  numInputs = atoi(&test[0][9]);
  /*printf("!!!! numInputs = %d\n", numInputs);*/
  fileptr = fopen(argv[2],"r");
  while(fgets(buff, sizeof(buff), fileptr) != NULL){
    numCases++;
  }
  fclose(fileptr);

  /*printf("numCases = %d\n",numCases);*/
  
  inputValues = malloc(numCases*sizeof(int*));
  
  for (k=0; k<numCases; k++){
    inputValues[k] = malloc(numInputs*sizeof(int));
    /*printf("Malloc row %d to %d inputs\n", k, numInputs);*/
  }
  

  for(j = 0; j<numCases; j++){
    for (k = 0; k<numInputs; k++){
      inputValues[j][k] = -1;
      /*printf("PRE: inputValues[%d][%d] = %d\n",j,k,inputValues[j][k]);*/
    }
  }

  
  fileptr = fopen(argv[2],"r");
  for(j = 0; j<numCases; j++){
    for (k = 0; k<numInputs; k++){
      fscanf(fileptr, "%d", &inputValues[j][k]);
      /*printf("inputValues[%d][%d] = %d\n",j,k,inputValues[j][k]);*/
    }
  }
  fclose(fileptr);
  
  for(j = 0; j<numCases; j++){
    for (k = 0; k<numInputs; k++){
      /* printf("Post: %d ", inputValues[j][k]);*/
    }
    /*printf("\n");*/
  }
  
  testToken = malloc(numLines*sizeof(char**));
 
  for(j=0; j<numLines; j++){
    testToken[j] = malloc(16*sizeof(char*));
    for(k=0; k<64; k++){
      testToken[j][k] = malloc(16);
    }
  }
  for(j=0; j<numLines; j++){
    p = strtok(test[j], " ");
    /*printf("p = %s\n", p);*/
    k = 0;
    while (p!= NULL){
      testToken[j][k] = p;
      k++;
      p = strtok(NULL, " ");
    }
  }
  for(j=0; j<numLines; j++){
    for(k=0; k<16; k++){
      /*printf("testToken[%d][%d] = %s\n",j,k,testToken[j][k]);*/
    }
  }

  numOutputs = atoi(testToken[1][1]);
  outputhead = (struct node *)malloc(sizeof(struct node));
  outputhead->id = *testToken[1][2];
  outputhead->next = NULL;

  ptr = outputhead;
  for(j=3; j<numOutputs+2; j++){
    ptr->next = (struct node*)malloc(sizeof(struct node)); 
    ptr = ptr->next;
    ptr->id = *testToken[1][j];
    ptr->next = NULL;
  }

  ptr = outputhead;
  while(ptr!=NULL){
    /*printf("output ptr->id = %c\n", ptr->id);*/
    ptr = ptr->next;
  }


  inputhead = (struct node *)malloc(sizeof(struct node));
  inputhead->id = *testToken[0][2];
  inputhead->next = NULL;

  ptr = inputhead;
  for(j=3; j<numInputs+2; j++){
    ptr->next = (struct node*)malloc(sizeof(struct node)); 
    ptr = ptr->next;
    ptr->id = *testToken[0][j];
    ptr->next = NULL;
  }

  ptr = inputhead;
  while(ptr!=NULL){
    /*printf("input ptr->id = %c\n", ptr->id);*/
    ptr = ptr->next;
  }

  for(n=0; n<numCases; n++){
    ptr = inputhead;
    ptr->val = inputValues[n][0];
    /*printf("inputValues[%d][0] = ptr->val = %d\n",j,inputValues[n][0]);*/
    ptr = ptr->next;
    k = 1;
    while(ptr != NULL){
      ptr->val = inputValues[n][k];
      /*printf("inputValues[%d][%d] = ptr->val = %d\n",j,k,inputValues[n][k]);*/
      ptr = ptr->next;
      k++;
    }
    /*printf("done loading inputs!\n");*/
    intermediate = NULL;
    for(k=2; k<numLines; k++){
      command = testToken[k][0];
      /*printf("line 309!\n");*/

      if(strcmp(command, "NOT") == 0){
	/*printf("NOT!\n");*/
	i1 = *testToken[k][1];
	o1 = *testToken[k][2];
	/*printf("before find!\n");*/
	ii1 = find(&inputhead,&outputhead,&intermediate,i1);
	/*printf("error here!\n");*/
	if (o1 >= 'a' && o1 <= 'z'){
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o1;
	    newInter->val = not(ii1);
	    newInter->next = intermediate;
	    intermediate = newInter;
	} else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o1){
		temp->val = not(ii1);
		break;
	      }
	      temp = temp->next;
	    }
	}
      }
      
      if(strcmp(command, "AND") == 0){
	/*printf("AND! \n");*/
	i1 = *testToken[k][1];
	i2 = *testToken[k][2];
	o1 = *testToken[k][3];
	/*printf("before this!\n");*/
	temp = intermediate;
	while(temp != NULL){
	  /*printf("intermediate: %c, value = %d\n", temp->id, temp->val);*/
	  temp = temp->next;
	}
	
	ii1 = find(&inputhead,&outputhead,&intermediate,i1);
	ii2 = find(&inputhead,&outputhead,&intermediate,i2);

	/*printf("before all this!\n");*/
	if (o1 >= 'a' && o1 <= 'z'){
	  /*printf("lowercase? o1 = %c \n",o1);*/
	  temp = intermediate;
	  newInter = (struct node *)malloc(sizeof(struct node));
	  newInter->id = o1;
	  newInter->val = and(ii1, ii2);
	  newInter->next = temp;
	  intermediate = newInter;
	} else {
	  /*printf("temp about to be set!\n");*/
	  temp = outputhead;
	  /*printf("here!329 \n");*/
	  while(temp!=NULL){
	    if(temp->id == o1){
	      temp->val = and(ii1, ii2);
	      break;
	    }
	    temp = temp->next;
	  }
	  /*printf("passed while!\n");*/
	}
	/*printf("AND successful \n");*/
      } else if (strcmp(command, "OR") == 0){
		
	i1 = *testToken[k][1];
	i2 = *testToken[k][2];
	o1 = *testToken[k][3];

	
	ii1 = find(&inputhead,&outputhead,&intermediate,i1);
	ii2 = find(&inputhead,&outputhead,&intermediate,i2);

	if (o1 >= 'a' && o1 <= 'z'){
	  temp = intermediate;
	  newInter = (struct node *)malloc(sizeof(struct node));
	  newInter->id = o1;
	  newInter->val = or(ii1, ii2);
	  newInter->next = temp;
	  intermediate = newInter;
	} else {
	  temp = outputhead;
	  while(temp!=NULL){
	    if(temp->id == o1){
	      temp->val = or(ii1, ii2);
	      break;
	    }
	    temp = temp->next;
	  }
	}

      } else if (strcmp(command, "MULTIPLEXER") == 0){
	
	multiType = *testToken[k][1];

	if (multiType == '2'){
	  i1 = *testToken[k][2];
	  i2 = *testToken[k][3];
	  s1 = *testToken[k][4];
	  o1 = *testToken[k][5];
	  
	  ii1 = find(&inputhead,&outputhead,&intermediate,i1);
	  ii2 = find(&inputhead,&outputhead,&intermediate,i2);
	  is1 = find(&inputhead,&outputhead,&intermediate,s1);

	  if (o1 >= 'a' && o1 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o1;
	    newInter->val = multi2(ii1, ii2, is1);
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o1){
		temp->val = multi2(ii1, ii2, is1);
		break;
	      }
	      temp = temp->next;
	    }
	  }
	}

	else if (multiType == '4'){
	  i1 = *testToken[k][2];
	  i2 = *testToken[k][3];
	  i3 = *testToken[k][4];
	  i4 = *testToken[k][5];
	  s1 = *testToken[k][6];
	  s2 = *testToken[k][7];
	  o1 = *testToken[k][8];

	 
	  ii1 = find(&inputhead,&outputhead,&intermediate,i1);
	  ii2 = find(&inputhead,&outputhead,&intermediate,i2);
	  ii3 = find(&inputhead,&outputhead,&intermediate,i3);
	  ii4 = find(&inputhead,&outputhead,&intermediate,i4);	  
	  is1 = find(&inputhead,&outputhead,&intermediate,s1);
	  is2 = find(&inputhead,&outputhead,&intermediate,s2);

	  if (o1 >= 'a' && o1 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o1;
	    newInter->val = multi4(ii1, ii2, ii3, ii4, is1, is2);
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o1){
		temp->val = multi4(ii1, ii2, ii3, ii4, is1, is2);
		break;
	      }
	      temp = temp->next;
	    }
	  }
	} else if (multiType == '8'){
	  i1 = *testToken[k][2];
	  i2 = *testToken[k][3];
	  i3 = *testToken[k][4];
	  i4 = *testToken[k][5];
	  i5 = *testToken[k][6];
	  i6 = *testToken[k][7];
	  i7 = *testToken[k][8];
	  i8 = *testToken[k][9];
	  s1 = *testToken[k][10];
	  s2 = *testToken[k][11];
	  s3 = *testToken[k][12];
	  o1 = *testToken[k][13];

	  /*printf("i1=%c, i2=%c, i3=%c, i4=%c, i5=%c, i6=%c, i7=%c, i8=%c\n",
	    i1,i2,i3,i4,i5,i6,i7,i8);*/
	   
	  ii1 = find(&inputhead,&outputhead,&intermediate,i1);
	  ii2 = find(&inputhead,&outputhead,&intermediate,i2);
	  ii3 = find(&inputhead,&outputhead,&intermediate,i3);
	  ii4 = find(&inputhead,&outputhead,&intermediate,i4);
	  ii5 = find(&inputhead,&outputhead,&intermediate,i5);
	  ii6 = find(&inputhead,&outputhead,&intermediate,i6);
	  ii7 = find(&inputhead,&outputhead,&intermediate,i7);
	  ii8 = find(&inputhead,&outputhead,&intermediate,i8);

	  /*printf("ii1=%d, ii2=%d, ii3=%d, ii4=%d, ii5=%d, ii6=%d, ii7=%d, ii8=%d\n",
	    ii1,ii2,ii3,ii4,ii5,ii6,ii7,ii8);*/
	  
	  is1 = find(&inputhead,&outputhead,&intermediate,s1);
	  is2 = find(&inputhead,&outputhead,&intermediate,s2);
	  is3 = find(&inputhead,&outputhead,&intermediate,s3);
	  /*printf("is1=%d, is2=%d, is3=%d\n",
	    is1,is2,is3);*/

	  if (o1 >= 'a' && o1 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o1;
	    newInter->val = multi8(ii1, ii2, ii3, ii4, ii5, ii6, ii7, ii8, is1, is2, is3);
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o1){
		temp->val = multi8(ii1, ii2, ii3, ii4, ii5, ii6, ii7, ii8, is1, is2, is3);
		break;
	      }
	      temp = temp->next;
	    }
	  }
	}
      } else if (strcmp(command, "DECODER") == 0){
	decoderType = *testToken[k][1];

	if(decoderType == '2'){
	  i1 = *testToken[k][2];
	  i2 = *testToken[k][3];
	  o1 = *testToken[k][4];
	  o2 = *testToken[k][5];
	  o3 = *testToken[k][6];
	  o4 = *testToken[k][7];
	 
	  ii1 = find(&inputhead,&outputhead,&intermediate,i1);
	  ii2 = find(&inputhead,&outputhead,&intermediate,i2);

	  decoderTemp = decoder2(ii1, ii2);

	 
	  if (o1 >= 'a' && o1 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o1;
	    newInter->val = decoderTemp[0];
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o1){
		temp->val = decoderTemp[0];
		break;
	      }
	      temp = temp->next;
	    }
	  }

	  if (o2 >= 'a' && o2 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o2;
	    newInter->val = decoderTemp[1];
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o2){
		temp->val = decoderTemp[1];
		break;
	      }
	      temp = temp->next;
	    }
	  }

	  if (o3 >= 'a' && o3 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o3;
	    newInter->val = decoderTemp[2];
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o3){
		temp->val = decoderTemp[2];
	      break;
	    }
	    temp = temp->next;
	  }
	}
	 
	  if (o4 >= 'a' && o4 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o4;
	    newInter->val = decoderTemp[3];
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o4){
		temp->val = decoderTemp[3];
		break;
	      }
	      temp = temp->next;
	    }
	  }

	 
	} else if (decoderType == '3'){
	  i1 = *testToken[k][2];
	  i2 = *testToken[k][3];
	  i3 = *testToken[k][4];
	 
	  o1 = *testToken[k][5];
	  o2 = *testToken[k][6];
	  o3 = *testToken[k][7];
	  o4 = *testToken[k][8];
	  o5 = *testToken[k][9];
	  o6 = *testToken[k][10];
	  o7 = *testToken[k][11];
	  o8 = *testToken[k][12];
	 	  
	  ii1 = find(&inputhead,&outputhead,&intermediate,i1);
	  ii2 = find(&inputhead,&outputhead,&intermediate,i2);
	  ii3 = find(&inputhead,&outputhead,&intermediate,i3);

	  decoderTemp = decoder3(ii1, ii2, ii3);


	  if (o1 >= 'a' && o1 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o1;
	    newInter->val = decoderTemp[0];
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o1){
		temp->val = decoderTemp[0];
		break;
	      }
	      temp = temp->next;
	    }
	  }
	
	  
	  if (o2 >= 'a' && o2 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o2;
	    newInter->val = decoderTemp[1];
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o2){
		temp->val = decoderTemp[1];
		break;
	      }
	      temp = temp->next;
	    }
	  }
	  
	  
	  if (o3 >= 'a' && o3 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o3;
	    newInter->val = decoderTemp[2];
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o3){
		temp->val = decoderTemp[2];
		break;
	      }
	      temp = temp->next;
	    }
	  }
	  
	  
	  if (o4 >= 'a' && o4 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o4;
	    newInter->val = decoderTemp[3];
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o4){
		temp->val = decoderTemp[3];
		break;
	      }
	      temp = temp->next;
	    }
	  }

	  if (o5 >= 'a' && o5 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o5;
	    newInter->val = decoderTemp[4];
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o5){
		temp->val = decoderTemp[4];
		break;
	      }
	      temp = temp->next;
	    }
	  }
	  if (o6 >= 'a' && o6 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o6;
	    newInter->val = decoderTemp[5];
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o6){
		temp->val = decoderTemp[5];
		break;
	      }
	      temp = temp->next;
	    }
	  }

	  if (o7 >= 'a' && o7 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o7;
	    newInter->val = decoderTemp[6];
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o7){
		temp->val = decoderTemp[6];
		break;
	      }
	      temp = temp->next;
	    }
	  }
	  if (o8 >= 'a' && o8 <= 'z'){
	    temp = intermediate;
	    newInter = (struct node *)malloc(sizeof(struct node));
	    newInter->id = o8;
	    newInter->val = decoderTemp[7];
	    newInter->next = temp;
	    intermediate = newInter;
	  } else {
	    temp = outputhead;
	    while(temp!=NULL){
	      if(temp->id == o8){
		temp->val = decoderTemp[7];
		break;
	      }
	      temp = temp->next;
	    }	 
	  }
	}
      }

    }
    ptr = outputhead;
    for(m=0;m<numOutputs;m++){
      printf("%d ", ptr->val);
      ptr = ptr->next;
    }
    printf("\n");
  }
     
}
  

