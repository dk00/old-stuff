#include<math.h>
#include<stdio.h>
//log2(N) + k*log2(10) <= x and x < log2(N+1) + k*log2(10)

main(){
double lg2=log10(2),log210=1/lg2;
double a,b;
int n,k;
for(k=0;k<20;k++)
    printf("%.13lf\n",log210*k-floor(log210*k));
while(scanf("%d",&n)!=EOF){
    a=log10(n)/lg2;
    b=log10(n+1)/lg2;
    printf("%.13lf %.13lf\n",a,b);
    for(k=(int)floor(log10(n))+2;;k++)
        if(ceil(log210*k+a)<b+log210*k)break;
    printf("%.13lf %.0lf\n",log210*k,ceil(log210*k+a));
}
}

