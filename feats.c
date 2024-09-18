#include "helper.h"
#include "feats.h"
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#define MAX_PROCESS_LIMIT 10500

void feats_lp(int limit){
  HANDLE ps_hd;
  PROCESSENTRY32 container;
  unsigned int counter =0,limit_t=limit; 
  if(limit_t==-1){
    limit_t = MAX_PROCESS_LIMIT;
    }
  ps_hd = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if(ps_hd == INVALID_HANDLE_VALUE){
    fprintf(stderr,"\n%sERROR : PROCESS SNAPSHOT FAILED : CODE %s%lu",RED_FG,RESET,GetLastError());
    return;
   }
  container.dwSize = sizeof(PROCESSENTRY32);

  if(!Process32First(ps_hd,&container)){
    fprintf(stderr,"\n%sERROR : PROCESS FETCHING FAILED : CODE %s%lu",RED_FG,RESET,GetLastError());
    CloseHandle(ps_hd);
    return;
  }
  fprintf(stdout, "\n%s%sPID %sPRIORITY %sNAME %sTHREADS %sPARENT %s", BLACK_FG, CYAN_BG, MAGENTA_BG, GREEN_BG, BLUE_BG,YELLOW_BG, RESET);
  while(Process32Next(ps_hd,&container)&&limit_t>0){
     fprintf(stdout,"\n%s%u %s%ld %s%s %s%ld %s%u %s",CYAN_FG,container.th32ProcessID,MAGENTA_FG,container.pcPriClassBase,GREEN_FG,container.szExeFile,BLUE_FG,container.cntThreads,YELLOW_FG,container.th32ParentProcessID,RESET);
  counter++;
  limit_t--;
  }
  if(limit==-1){
    fprintf(stdout,"\n%s%sPROCESSES RUNNING : %s %d",BLACK_FG,WHITE_BG,RESET,counter-1);
    fprintf(stdout,"\n%sLast process is the script itself, decremented from counter%s\n",YELLOW_FG,RESET);
  }
  else{
    fprintf(stdout,"\n%s%sPROCESSES FETCHED : %s %d",BLACK_FG,WHITE_BG,RESET,counter);
  }
}
