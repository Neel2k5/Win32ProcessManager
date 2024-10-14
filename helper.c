/**
 *  Copyright 2024 Swapnaneel Dutta

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   limitations under the License.

 */



#include <stdio.h>
#include "helper.h"
#include <string.h>
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

char* helper_fnstr(char *path){
  char *ret;
  ret  = strrchr(path, '\\');
  ret++;
  return ret;

}
