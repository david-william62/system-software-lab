#include <stdio.h>

void main() {
  float awt,att,twt=0,ttt=0;
  int n;
  printf("Enter no of processes");
  scanf("%d",&n);
  int wt[n],tt[n],bt[n],p[n];

  for(int i=0;i<n;i++) {
    printf("\nEnter burst time of process p%d: ",i+1);
    scanf("%d",&bt[i]);
    p[i] = i+1;
  }

  for(int i=0;i<n-1;i++) {
    for(int j=0;j<n-i-1;j++) {
      if(bt[j]>bt[j+1]) {
        int temp = bt[j];
        bt[j] = bt[j+1];
        bt[j+1] = temp;

        temp = p[j];
        p[j] = p[j+1];
        p[j+1] = temp;
      }
    }
  }
  wt[0]=0;
  tt[0]=bt[0];
  twt += wt[0];
  ttt += tt[0];

  for(int i=1;i<n;i++) {
    wt[i] = wt[i-1]+bt[i-1];
    tt[i] = wt[i]+bt[i];

    ttt += tt[i];
    twt += wt[i];
  }
  awt = twt/n;
  att = ttt/n;
  
  printf("\nProcess\tBurst time\tWaiting time\tTurnaround time\n");
  for(int i=0;i<n;i++) {
    printf("p%d\t%d\t\t%d\t\t%d\n",p[i],bt[i],wt[i],tt[i]);
  }
  printf("Average waiting time: %f\n",awt);
  printf("Average Turnaround time: %f\n",att);
}
