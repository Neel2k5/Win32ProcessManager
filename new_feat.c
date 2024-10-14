#include "helper.h"
#include "feats.h"
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <stdbool.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESS_LIMIT 10500
#define PATH_LIM 256

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
    fprintf(stdout, "%s[pid]%s[parent]%s name%s\n", CYAN_BG,MAGENTA_BG, YELLOW_BG, RESET);
    while(tp!=NULL){
      prd(0,tp,&counter,count);
      tp=tp->next;

    }
    fprintf(stdout,"\nTotal processes displayed: %d\n",count);
   
    CloseHandle(ps_hd); 
}

int main() {
    feats_tree(0,-1);
    printf("\n\n");
    feats_tree(0,30);
    return 0;
}

