#include<stdio.h>
#include<math.h>
int gcd(int a,int b){
    return a?gcd(b%a,a):b;
}
main(){
int i,j,n,p,r,num[100];
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)scanf("%d",&num[i]);
    for(p=r=i=0;i<n;i++)
        for(j=i+1;j<n;j++){
            r++;
            if(gcd(num[i],num[j])==1)p++;
        }
    if(p)printf("%.6lf\n",sqrt(6*r/(double)p));
    else puts("No estimate for this data set.");
}
}
