/* @JUDGE_ID:  58589NF  591  c++  "Box of Bricks"*/
#include<stdio.h>
int main(){
int n,h[50],avg,sum,i,set=1;
while(1){
    scanf("%d",&n);
    if(n<=0)
        break;
    for(i=0,sum=0;i<n;i++){
        scanf("%d",&h[i]);
        sum+=h[i];
    }
    avg=sum/n;
    sum=0;
    for(i=0;i<n;i++)
        sum+=(h[i]-avg>0?h[i]-avg:0);
    printf("Set #%d\nThe minimum number of moves is %d.\n",set++,sum);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
