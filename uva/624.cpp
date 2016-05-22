#include<stdio.h>
long s[10000];
main(){
long n,t,len[21],i,j,max;
while(scanf("%ld %ld",&n,&t)!=EOF){
    for(max=i=0;i<=n;i++)s[i]=0;
    for(i=0;i<t;i++){
        scanf("%ld",&len[i]);
        for(j=max+len[i]<?n;j>len[i];j--){
            if(!s[j] && s[j-len[i]]){
                s[j]=s[j-len[i]]|(1<<i);
                max>?=j;
            }
        }
        if(!s[len[i]])s[len[i]]=(1<<i);
        max>?=len[i];
    }
    for(i=0;i<t;i++)if(s[max]&(1<<i))printf("%ld ",len[i]);
    printf("sum:%ld\n",max);
}
}
