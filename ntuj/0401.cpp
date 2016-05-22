#include<cstdio>
const int N=584898,M=1000000;
int s[M+1],p[M+1],x[M+1];
main()
{
    int i,j,k;
    s[1]=1;
    for(i=2;i<=M;i++)p[i]=1;
    for(i=j=2;i<=N;i++)
    {
        s[j]=i;
        if(p[j/p[j]]==1)
            for(j/=p[j],x[j]=k=j;k<=M;k+=j)
                p[k]=j;
        for(k=j;k>1;k/=p[k])
            while(s[x[p[k]]])x[p[k]]+=p[k];
        for(k=j,j=x[p[j]];k>1;k/=p[k])
            j<?=x[p[k]];
    }
    while(scanf("%d",&i)>0 && i)
        printf("The number %d appears in location %d.\n",i,s[i]);
}
