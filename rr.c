#include <stdio.h> 
#include <stdlib.h>
struct process {
  int id;
  struct process *next;
  int bt;
  int tt;
  int wt;
};
struct process *head = NULL;

struct process* createProcess(int id, int bt) {
  struct process *p = (struct process*)malloc(sizeof(struct process));
  p->id = id;
  p->bt = bt;
  p->tt = 0;
  p->wt = 0;
  p->next = NULL;

  return p;
}

void addProcess (int id, int bt) {
  struct process *p = createProcess(id, bt);
  if(head=NULL) head = p;
  else {
    struct process *temp = head;
    while(temp->next != NULL) temp = temp->next;
    temp->next=p;
  }
}

void main() {
  int n,tq,i;
  printf("Enter the time quantum: ");
  scanf("%d",&tq);
  printf("Enter the number of processes");
  scanf("%d",&n);
  for(i=0;i<n;i++) {
    int bt;
    printf("Enter burst time for process p%d",i);
    scanf("%d",&bt);
    addProcess(i , bt);
  }
}
