#include "helper.h"
#include "feats.h"
#include <stdbool.h>
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
  CloseHandle(ps_hd);
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
  fprintf(stdout,"\n%s%sPROCESS ID : %s %s%d%s",CYAN_BG,BLACK_FG,RESET,CYAN_FG,pID,RESET);
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
    fprintf(stdout,"\n%s%sRAM USAGE : %s %s%lf KB%s",RED_BG,BLACK_FG,RESET,RED_FG,((double)(mem_container.PeakPagefileUsage))/1000,RESET); 
  }
CloseHandle(ps_hd);
}

void feats_kill(unsigned int pID){
  HANDLE ps_hd;
  ps_hd = OpenProcess(PROCESS_TERMINATE, FALSE, pID);
  //printf("\nreaches1");//debugging
  fprintf(stdout,"\n%s%sPROCESS ID : %s%s%u%s",BLACK_FG,CYAN_BG,RESET,CYAN_FG,pID,RESET);
  //printf("\nreaches2");//debugging
  if(ps_hd==NULL){
    fprintf(stderr,"\n%sERROR : PROCESS FETCHING FAILED : CODE %s%lu",RED_FG,RESET,GetLastError());
    CloseHandle(ps_hd);
    return;
  }
  if(!TerminateProcess(ps_hd, 0)){
    fprintf(stderr,"\n%sERROR : PROCESS TERMINATION FAILED : CODE %s%lu",RED_FG,RESET,GetLastError());
    CloseHandle(ps_hd);
    return;
  }
  fprintf(stdout,"\n%sSucessfully Terminated\n%s",GREEN_FG,RESET);
  CloseHandle(ps_hd);

}



//TREE AREA

typedef struct PID {
    unsigned int pid;
    char *name;
    unsigned int parent;
    bool visited;
    struct PID *next;
} PID;

PID* successive_addnode(PID *location, unsigned int pid, unsigned int parent, char *name) {
    location->next = (PID*)malloc(sizeof(PID));
    location->next->next = NULL;
    location->next->pid = pid;
    location->next->name = (char*)malloc(strlen(name) + 1);
    strcpy(location->next->name, name);
    location->next->parent = parent;
    return location->next;
}



//processdisplay
void prd(unsigned int depth,PID *list,int *counter,int limit){
  PID *ptr = list;
  if(ptr==NULL||ptr->visited||*counter==limit)return;

    for(size_t i=0;i<depth;i++)
      {
        fprintf(stdout,"%s|%s", BLUE_FG, RESET);
    }
    fprintf(stdout, "%s-%s", BLUE_FG, RESET);
    fprintf(stdout, "%s[%d]%s[%d]%s %s%s\n", CYAN_FG, ptr->pid, MAGENTA_FG, ptr->parent, YELLOW_FG, ptr->name, RESET);
    
    (*counter)++;
    ptr->visited=true;
    unsigned int pp = ptr -> pid;
    ptr = ptr->next;
    while(ptr!=NULL){
      if(ptr->parent==pp){
         prd(depth+1,ptr,counter,limit);
      }
      ptr = ptr->next;
    }
   
}
//actual function
void feats_tree(unsigned int depth,int limit) {
    PID *head, *tp;
    unsigned int pcount = 0;
    HANDLE ps_hd;
    PROCESSENTRY32 container;

    ps_hd = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (ps_hd == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "\n%sERROR : PROCESS SNAPSHOT FAILED : CODE %s%lu", RED_FG, RESET, GetLastError());
        return;
    }

    container.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(ps_hd, &container)) {
        fprintf(stderr, "\n%sERROR : PROCESS FETCHING FAILED : CODE %s%lu", RED_FG, RESET, GetLastError());
        CloseHandle(ps_hd);
        return;
    }

    head = (PID*)malloc(sizeof(PID));
    head->next = NULL;
    head->pid = container.th32ProcessID;
    head->name = (char*)malloc(strlen(container.szExeFile) + 1);
    strcpy(head->name, container.szExeFile);
    head->parent = container.th32ParentProcessID;
    tp = head;
    pcount++;

    while (Process32Next(ps_hd, &container)) {
        tp->next = successive_addnode(tp, container.th32ProcessID, container.th32ParentProcessID, container.szExeFile);
        tp->next->visited = false;
        pcount++;
        tp = tp->next;
    }

    tp = head;
    int count,counter=0;
    if(limit>0)count=limit;
    else count=pcount;
    // tree view
    fprintf(stdout, "%s[pid]%s[parent]%s name%s\n", CYAN_BG,MAGENTA_BG, YELLOW_BG, RESET);
    while(tp!=NULL){
      prd(0,tp,&counter,count);
      tp=tp->next;

    }
    fprintf(stdout,"\nTotal processes displayed: %d\n",count);
   
    CloseHandle(ps_hd); 
}

