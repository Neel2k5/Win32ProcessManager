#include <stdio.h>
#include "helper.h"

void helper_ugdisplay(void){
FILE *ug;

  ug = fopen("ug_wpm.txt","r");
  char buffer;
  if(ug == NULL){
    fprintf(stderr,"\n ERROR : CANT FIND ug_wpm.txt IN DIRECTORY\n");
    return;}
  fprintf(stdout,"\n");
  while((buffer=fgetc(ug))!=EOF){
    fprintf(stdout,"%c",buffer);
  } fclose(ug);
}
