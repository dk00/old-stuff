#include<math.h>
#include<stdio.h>
#include<stdlib.h>
main(){
int i,j,n,min,px[10000],py[10000];
while(scanf("%d",&n)!=EOF && n){
    for(i=0;i<n;i++)scanf("%d %d",&px[i],&py[i]);
    min=100000000;
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++){
            min<?=((px[i]-px[j])*(px[i]-px[j])+(py[i]-py[j])*(py[i]-py[j]));
        }
    if(sqrt(min)<10000.0)
        printf("%.4lf\n",sqrt(min));
    else
        puts("INFINITY");
}
}
