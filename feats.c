#include "helper.h"
#include "feats.h"
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <tchar.h>
#define MAX_PROCESS_LIMIT 10500
#define PATH_LIM 256

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
  CloseHandle(ps_hd);
  if(limit==-1){
    fprintf(stdout,"\n%s%sPROCESSES RUNNING : %s %d",BLACK_FG,WHITE_BG,RESET,counter-1);
    fprintf(stdout,"\n%sLast process is the script itself, decremented from counter%s\n",YELLOW_FG,RESET);
  }
  else{
    fprintf(stdout,"\n%s%sPROCESSES FETCHED : %s %d",BLACK_FG,WHITE_BG,RESET,counter);
  }
}


void feats_psd(unsigned int pID){
  HANDLE ps_hd;
  PROCESS_MEMORY_COUNTERS mem_container;
  TCHAR *origin,path[PATH_LIM];
  ps_hd =  OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pID);
  if(ps_hd==NULL){
     fprintf(stderr,"\n%sERROR : PROCESS FETCHING FAILED : CODE %s%lu",RED_FG,RESET,GetLastError());
     CloseHandle(ps_hd);
     return;
  }
  fprintf(stdout,"\n\n%s%sPROCESS ID : %s %s%d%s",MAGENTA_BG,BLACK_FG,RESET,MAGENTA_FG,pID,RESET);
  if(!GetModuleFileNameEx(ps_hd,NULL,path,PATH_LIM)){
    fprintf(stderr,"\n%sERROR : PROCESS ORIGIN FETCHING FAILED : CODE %s%lu",RED_FG,RESET,GetLastError());
  }
  else{
    origin = helper_fnstr(path);
    fprintf(stdout,"\n%s%sPROCESS ORIGIN : %s %s%s%s",GREEN_BG,BLACK_FG,RESET,GREEN_FG,origin,RESET);
    fprintf(stdout,"\n%s%sPROCESS ORIGIN PATH : %s %s%s%s",YELLOW_BG,BLACK_FG,RESET,YELLOW_FG,path,RESET);
  }

  if(!GetProcessMemoryInfo(ps_hd, (PPROCESS_MEMORY_COUNTERS)&mem_container, sizeof(mem_container))){
     fprintf(stderr,"\n%sERROR : PROCESS MEMORY INFO FETCHING FAILED : CODE %s%lu",RED_FG,RESET,GetLastError());
  }
  else{
    fprintf(stdout,"\n%s%sRAM USAGE : %s %s%lf KB%s",CYAN_BG,BLACK_FG,RESET,CYAN_FG,((double)(mem_container.PeakPagefileUsage))/1000,RESET); 
  }

}
