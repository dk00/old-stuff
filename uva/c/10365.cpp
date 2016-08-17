#include<stdio.h>
main(){
int i,j,k,n,t,min;
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    min=2147483647;
    for(i=1;i*i*i<=n;i++)
        for(j=i;i*j*j<=n;j++)
            for(k=j;i*j*k<=n;k++)
                if(i*j*k==n)
                    min<?=(i*j+i*k+j*k);
    printf("%d\n",min*2);
}
}
