/*
PROG: pfact
LANG: C++
ID: s0000151
*/
#include<cstdio>
char notp[32000];
int p[10000];
main()
{
    freopen("pfact.in","r",stdin);
    freopen("pfact.out","w",stdout);
    int i,j,n;
    p[0]=2,n=1;
    for(i=3;i<31622;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*i;j<31622;j+=i*2)
            notp[j]=1;
        p[n++]=i;
    }
    scanf("%d",&j);
    for(i=0;i<n && p[i]<=j;i++)
        while(j%p[i]==0)
            printf("%d\n",p[i]),j/=p[i];
    if(j>1)printf("%d\n",j);
    scanf(" ");
}
