#include<stdio.h>
long s[10000];
main(){
long n,t,len[21],i,j,max;
while(scanf("%ld %ld",&n,&t)!=EOF){
    for(max=i=1;i<=n;i++)s[i]=0;
    s[0]=1;s[0]=s[0]<<25;
    for(i=0;i<t;i++){
        scanf("%ld",&len[i]);
        for(j=0;j+len[i]<=n;j++){
            if(!(s[j]&(1<<i)) && s[j]){
                s[j+len[i]]=s[j]|(1<<i);
                max>?=j+len[i];
            }
        }
    }
    for(i=0;i<t;i++)
        if(s[max]&(1<<i))printf("%ld ",len[i]);
    printf("sum:%ld\n",max);
}
}
