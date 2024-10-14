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
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "feats.h"
int main(int argc,char *argv[]){
  fprintf(stdout,"\n%s%sARGS PASSED :%s %d\n",WHITE_BG,BLACK_FG,RESET,argc-1);
  if(argc<2){
    fprintf(stderr,"\n%sERROR : TOO LITTLE ARGUMENTS%s",RED_FG,RESET);
    helper_ugdisplay();
    return -1;
  }

  else{
  if(strcmpi(argv[1],"lp")==0){
    if(argc>2){
      feats_lp(atoi(argv[2]));
      return 0;
    }
    feats_lp(-1);
  } 
  else if(strcmpi(argv[1],"psd")==0){
    if(argc<3){
      fprintf(stderr,"\n%sERROR : TOO LITTLE ARGUMENTS FOR SPECIFIED COMMAND%s",RED_FG,RESET);
      return -1;
    }
    feats_psd(atoi(argv[2]));
  }
  else if(strcmpi(argv[1],"kill")==0){
    if(argc<3){
      fprintf(stderr,"\n%sERROR : TOO LITTLE ARGUMENTS FOR SPECIFIED COMMAND%s",RED_FG,RESET);
      return -1;     } 
    feats_kill(atoi(argv[2]));
  }
  else if(strcmpi(argv[1],"help")==0){
    helper_ugdisplay();
  }
  else if(strcmpi(argv[1],"tree")==0){
    if(argc>2){
      feats_tree(0,atoi(argv[2]));
      return 0;
    }
    else {
    feats_tree(0,-1);
    return 0;
  }
  }
  else{
    fprintf(stderr,"\n%sERROR : NO VALID COMMAND%s",RED_FG,RESET);
    helper_ugdisplay();
    return -1;
  }
  }
  return 0;


}
