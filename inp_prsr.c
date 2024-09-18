#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"
#include "feats.h"
int main(int argc,char *argv[]){
  fprintf(stdout,"\n%s%sARGS PASSED :%s %d",WHITE_BG,BLACK_FG,RESET,argc-1);
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
  else if(strcmpi(argv[1],"dp")==0){
    if(argc<3){
      fprintf(stderr,"\n%sERROR : TOO LITTLE ARGUMENTS FOR SPECIFIED COMMAND%s",RED_FG,RESET);
      return -1;
    }
    //Describe process
  }
  else if(strcmpi(argv[1],"help")==0){
    helper_ugdisplay();
  }
  else{
    fprintf(stderr,"\n%sERROR : NO VALID COMMAND%s",RED_FG,RESET);
    helper_ugdisplay();
    return -1;
  }
  }
  return 0;


}
