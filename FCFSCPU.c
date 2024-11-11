#include<stdio.h>
int main(){
    int no_process,bt[10],wt[10],tat[10];
    float avg_wt,avg_tat;

    printf("Enter number of process\n");
    scanf("%d",&no_process);
    
    printf("Enter burst time of:\n");
    for(int i=0;i<no_process;i++){
        printf("Process %d",i+1);
        scanf("%d",&bt[i]);
       
    }

    wt[0]=0;
    for(int i=1;i<no_process;i++){
        wt[i]=wt[i-1]+bt[i-1]; 
        tat[i-1]=wt[i-1]+bt[i-1];         
    }   
    tat[no_process-1]=wt[no_process-1]+bt[no_process-1];

	printf("Process\tBurst Time\tWaiting Time\tcompletion time\tTurnaround Time\n");
    for(int i=0;i<no_process;i++){
        printf("%d\t%d\t\t%d\t%d\t%d\n",i+1,bt[i],wt[i],tat[i],tat[i]);        
    }

    printf("Gantt Chart : ");
    for(int i=0;i<no_process;i++){
        printf("P%d_",i+1);
        avg_wt+=wt[i];      
        avg_tat+=tat[i];      
    }

    avg_tat/=no_process;     
    avg_wt/=no_process; 

    printf("\nAverage waiting time : %f",avg_wt);
    printf("\nAverage turnaround time : %f",avg_tat);

}