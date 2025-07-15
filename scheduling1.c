#include <stdio.h>

void main() {
  float awt,att,twt=0,ttt=0;
  int n;
  printf("Enter no of processes: ");
  scanf("%d",&n);
  int wt[n],tt[n],bt[n];
  for(int i=0;i<n;i++) {
    printf("\nEnter burst time of process p%d: ",i+1);
    scanf("%d",&bt[i]);
  }
  wt[0]=0;
  tt[0]=bt[0];
  twt += wt[0];
  ttt += tt[0];
  for(int i=1;i<n;i++) {
    wt[i] = wt[i-1]+bt[i-1];
    tt[i] = wt[i]+bt[i];

    twt += wt[i];
    ttt += tt[i];
  }
  awt = twt/n;
  att = ttt/n;

  printf("Process\tBurst Time\tWaiting time\tTurnaround Time\n");
  for(int i=0;i<n;i++) {
    printf("%d\t%d\t\t%d\t\t%d\n",i+1,bt[i],wt[i],tt[i]);
  }
  printf("Average waiting time: %f\n",awt);
  printf("average turnaround time: %f\n",att);
}
