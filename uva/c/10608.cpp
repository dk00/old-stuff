#include<stdio.h>
main(){
long t,n,m,i,j,a,b,set[30001],deep[30001],num[30001];
scanf("%ld",&t);
while(t--){
    scanf("%ld %ld",&n,&m);
    for(i=1;i<=n;i++){
        set[i]=i;
        num[i]=0;
    }
    while(m--){
        scanf("%ld %ld",&a,&b);
        for(i=a;i!=set[i];i=set[i]);
        for(j=b;j!=set[j];j=set[j]);
        if(i<j)set[j]=i;
        else if(i>j)set[i]=j;
    }
    for(i=1;i<=n;i++){
        for(j=i;set[j]!=j;j=set[j]);
        num[j]++;
    }
    for(a=i=1;i<=n;i++)a>?=num[i];
    printf("%ld\n",a);
}
}
