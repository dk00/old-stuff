#include<stdio.h>
long long s[51],c[51][51];
main(){
int i,j,k,n,p,q,r,t;
long long sum;
s[0]=1,s[1]=1;
for(i=0;i<=50;i++){
    c[i][0]=1;
    for(j=1;j<=i;j++)
        c[i][j]=c[i-1][j-1]+c[i-1][j];
}
for(i=2;i<=50;i++){
    s[i]=s[i-1];
    for(j=i/2;j<=i-1;j++)
        s[i]+=c[i-1][j];
}
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    if(!n){
        puts("0");
        continue;
    }
    for(i=0,k=1;k*2<=n;k<<=1,i++);
    r=k;
    sum=s[i];
    p=i+1;
    q=1;
    while(k>>=1,i-->2){
        r|=k;
        if(!i)
            if(q+q>p)sum++;
        if(n&k){
            for(j=(p/2-q+1)>?0;j<=i;j++)
                sum+=c[i][j];
            q++;
        }
    }
    for(r;r<=n;r++){
        for(k=r,j=i=0;k>0;j+=k&1,k>>=1,i++);
        if(j+j>i)sum++;
    }
    printf(":%d\n",sum);
}
}
