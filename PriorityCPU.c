#include<stdio.h>
int main(){
    int no_process,process[10],bt[10],wt[10],tat[10],priority[10],temp;
    float avg_wt,avg_tat;

    printf("Enter number of process\n");
    scanf("%d",&no_process);
    
    printf("Enter burst time and priority of:\n");
    for(int i=0;i<no_process;i++){
        printf("Process %d",i+1);
        scanf("%d",&bt[i]);
        scanf("%d",&priority[i]);
        process[i]=i+1;        
    }

    for(int i=0;i<no_process;i++){
        for(int j=0;j<no_process-i-1;j++){

            if(priority[j]>priority[j+1]){
                temp=priority[j];
                priority[j]=priority[j+1];
                priority[j+1]=temp;

                temp=bt[j];
                bt[j]=bt[j+1];
                bt[j+1]=temp;

                temp=process[j];
                process[j]=process[j+1];
                process[j+1]=temp;
            }
    }
    }

    wt[0]=0;
    for(int i=1;i<no_process;i++){
        wt[i]=wt[i-1]+bt[i-1]; 
        tat[i-1]=wt[i-1]+bt[i-1];         
    }
    tat[no_process-1]=wt[no_process-1]+bt[no_process-1];

	printf("Process\tBurst Time\tWaiting Time\tcompletion time\tTurnaround Time\n");
    for(int i=0;i<no_process;i++){
        printf("%d\t%d\t\t%d\t%d\t%d\n",process[i],bt[i],wt[i],tat[i],tat[i]);        
    }

    printf("Gantt Chart : ");
    for(int i=0;i<no_process;i++){
        printf("P%d_",process[i]);
        avg_wt+=wt[i];      
        avg_tat+=tat[i];      
    }

    avg_tat/=no_process;     
    avg_wt/=no_process; 

    printf("\nAverage waiting time : %f",avg_wt);
    printf("\nAverage turnaround time : %f",avg_tat);

}