#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    int req[50],curr_pos=0,THM,num_req;
    
    printf("Enter number of requests");
    scanf("%d",&num_req);
    
    printf("Enter requests");
    for(int i =0;i<num_req;i++)
    {
        scanf("%d",&req[i]);
        printf("\t");
  
    printf("Enter current pointer position");
        scanf("%d",&curr_pos);
     
    THM+=abs(req[0]-curr_pos);
    for(int i=1;i<num_req;i++)
    {
        THM+=abs(req[i]-req[i-1]);
    }
    
    printf("Total head movement is : %d",THM);


    return 0;
}
}