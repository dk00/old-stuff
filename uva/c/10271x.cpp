#include<stdio.h>
#include<stdlib.h>
main(){
long *help1,*help2,len[5005],i,j,k,t,n,p,q,*tmp;
help1=(long *)malloc(sizeof(long)*1010);
help2=(long *)malloc(sizeof(long)*1010);
scanf("%ld",&t);
while(t-- && scanf("%ld %ld",&k,&n)){
    for(i=0;i<n;i++)scanf("%ld",&len[i]);
    for(i=1;i<=k+8;i++)help2[i]=help1[i]=2147483647;
    help2[0]=help1[0]=0;
    for(i=n-3;i>=0;i--){
        p=len[i+1]-len[i];
        for(p*=p,j=1;j*3<=n-i && j<=k+8;j++){
            q=p+help2[j-1];
            if(help2[j]<q)q=help2[j];
            if(q<help1[j])
                help1[j]=q;
        }
        tmp=help1;help1=help2;help2=tmp;
    }
    printf("%ld\n",help2[k+8]<help1[k+8]?help2[k+8]:help1[k+8]);
}
}
