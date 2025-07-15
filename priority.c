#include <stdio.h>

struct process {
  int id;
  int pri;
  int tt;
  int wt;
  int bt;
};

void main() {
  float awt, att, twt=0, ttt=0;
  int n;
  printf("Enter no of processes: ");
  scanf("%d", &n);
  struct process p[n];
  int i;
  printf("\nEnter the priority of each process:\n");
  for(i=0;i<n;i++){
    p[i].id=i;
    scanf("%d",&p[i].pri);
  }
  printf("Enter burst time of each process: \n");
  for(i=0;i<n;i++) {
    scanf("%d",&p[i].bt);
  }
  for(i=0;i<n-1;i++)
    for(int j=0;j<n-i-1;j++) {
      struct process t;
      if(p[i].pri > p[i+1].pri) {
        t = p[i];
        p[i] = p[i+1];
        p[i+1] = t;
      }
    }
  p[0].wt = 0;
  p[0].tt = p[0].bt;
  twt += p[0].wt;
  ttt += p[0].tt;

  for(i=1;i<n;i++) {
    p[i].wt = p[i-1].wt + p[i-1].bt;
    p[i].tt = p[i].wt + p[i].bt;

    twt += p[i].wt;
    ttt += p[i].tt;
  }
  awt = twt/n;
  att = ttt/n;
  
  printf("\nProcess\tPriority\tBurst time\tWaiting time\tTurnaround time\n");
  for(int i=0;i<n;i++) {
    printf("p%d\t%d\t\t%d\t\t%d\t\t%d\n",p[i].id,p[i].pri,p[i].bt,p[i].wt,p[i].tt);
  }
  printf("Average waiting time: %f\n",awt);
  printf("Average Turnaround time: %f\n",att);

}
