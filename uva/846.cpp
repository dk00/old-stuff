#include<stdio.h>
long step[92682];
main(){
long i,j,t,k,m;
step[0]=0;
for(i=1;i<92682;i++)
    step[i]=step[i-1]+(i+1)/2;
scanf("%ld",&t);
while(t--){
    scanf("%ld %ld",&i,&j);
    k=j-i;
    if(!k){puts("0");continue;}
    for(i=0,j=92681,m=j/2;j-i>5;m=(i+j)/2){
        if(step[m]>=k && step[m-1]<k)break;
        if(step[m]<k)i=m+1;
        else j=m-1;
    }
    for(m=m-5>?0;;m++)if(step[m]>=k)break;
    printf("%ld\n",m);
}
}
