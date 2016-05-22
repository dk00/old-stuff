#include<stdio.h>
int swp;
main(){
int i,j,n,tt,t[10000];
scanf("%d",&tt);
while(tt--){
    scanf("%d",&n);
    for(i=0;i<n;i++)scanf("%d",&t[i]);
    for(swp=i=0;i<n;i++)
        for(j=1;j<n;j++)
            if(t[j-1]>t[j]){
                t[j-1]+=t[j];
                t[j]=t[j-1]-t[j];
                t[j-1]-=t[j];
                swp++;
            }
    printf("Optimal train swapping takes %d swaps.\n",swp);
}
}
