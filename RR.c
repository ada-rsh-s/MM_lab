#include<stdio.h>
int main(){
    int no_process,bt[10],rem_bt[10],wt[10],tat[10],qt,total_time=0;
    float avg_wt,avg_tat;

    printf("Enter number of process: ");
	scanf("%d",&no_process);
    printf("Enter time quantam: ");
	scanf("%d",&qt);

	printf("Enter burst time of process: ");
	for(int i=0;i<no_process;i++)
	{
		scanf("%d",&bt[i]);
        rem_bt[i]=bt[i];
        tat[i]=0;
	}

    printf("Gantt chart : ");
    while(1){
      int flag = 0;
      for(int i = 0; i < no_process; i++) {
         if(rem_bt[i] > 0) {
           flag = 1; 
           int temp = (rem_bt[i] >= qt) ? qt : rem_bt[i];
           total_time += temp;
           rem_bt[i] -= temp;

           if(rem_bt[i] == 0) 
            tat[i] = total_time; 
        
           printf("P%d_", i + 1);
         }
      }
      if (!flag) break; 
    }

    for(int i=0;i<no_process;i++){
        wt[i]=tat[i]-bt[i]; 
        avg_wt+=wt[i];      
        avg_tat+=tat[i];  
    }
    
	printf("\nProcess\tBurst Time\tWaiting Time\tcompletion time\tTurnaround Time\n");
    for(int i=0;i<no_process;i++){
        printf("%d\t%d\t\t%d\t%d\t%d\n",i+1,bt[i],wt[i],tat[i],tat[i]);        
    }

    avg_tat/=no_process;     
    avg_wt/=no_process; 
    printf("\nAverage waiting time : %f",avg_wt);
    printf("\nAverage turnaround time : %f",avg_tat);
}