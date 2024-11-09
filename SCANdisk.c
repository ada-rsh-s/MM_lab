#include<stdio.h>
#include<stdlib.h>

int main(){
    int num_req,req[20],move,curr_p,index,sequence[20],head_move,temp,size;
    printf("Enter number of requests");
    scanf("%d",&num_req);

    printf("Enter the requests");
    for(int i=0;i<num_req;i++){
        scanf("%d",&req[i]);
    }

    printf("Enter the movement side");
    scanf("%d",&move);
    
    printf("Enter the current position");
    scanf("%d",&curr_p);
    
    printf("Enter the size");
    scanf("%d",&size);
    size-=1;
    
    for(int i=0;i<num_req;i++){   
      for(int j=0;j<num_req-i-1;j++){
        if(req[j]>req[j+1]){
            temp=req[j];
            req[j]=req[j+1];
            req[j+1]=temp;
        }
      }
    }

    for(int i=0;i<num_req;i++){
        if(curr_p<req[i]){
            index=i;
            break;
        }
    }
    int k = 0;

    if (move == 1) { 
        for (int i = index; i < num_req; i++) {
            sequence[k++] = req[i];
        }
         sequence[k++] = size;
        for (int i = index - 1; i >= 0; i--) {
            sequence[k++] = req[i];
        }
        head_move=abs(curr_p-size);
        head_move+=(abs(size-req[0]));

    } else {
        for (int i = index - 1; i >= 0; i--) {
            sequence[k++] = req[i];
        }
         sequence[k++] = 0;
        for (int i = index; i < num_req; i++) {
            sequence[k++] = req[i];
        }
        head_move=curr_p;
        head_move+=req[num_req-1];
    }
    
    printf("%d",curr_p);
    for(int i=0;i<k;i++){
        printf("-> %d",sequence[i]);      
    }
    printf("\n");

    printf("Head movement = %d",head_move);      
     
}