#include<stdio.h>
main(){
    long long fact[21],resl;
    int i,n,ele[26],k,set;
    char c;
    for(i=fact[0]=1;i<21;i++)
    {
        fact[i]=fact[i-1]*i;
    }
    scanf("%d%c",&n,&c);
    for(set=1;set<=n;set++)
    {
        for(i=0;i<26;i++)
        {
            ele[i]=0;
        }
        scanf("%c",&c);
        for(k=0;c!='\n';k++)
        {
            ele[c-'A']++;
            scanf("%c",&c);
        }
        for(i=0,resl=fact[k];i<26;i++)
        {
            resl/=fact[ele[i]];
        }
        printf("Data set %d: ",set);
        printf("%lld\n",resl);
    }
}
