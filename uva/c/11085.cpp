#include<cstdio>
int n,s[92][8],c[8],r[8],r1[15],r2[15];
inline void go(int v)
{
    if(v>=8)
    {
        for(v=0;v<8;v++)
            s[n][v]=r[v];
        n++;
        return;
    }
    for(int i=0;i<8;i++)
        if(c[i]+r1[i+v]+r2[i-v+7]==0)
        {
            c[i]++,r1[i+v]++,r2[i-v+7]++;
            r[v]=i+1;
            go(v+1);
            c[i]--,r1[i+v]--,r2[i-v+7]--;
        }
}
main()
{
    go(0);
    int i,j,k,min,C=1;
    while(scanf("%d",&r[0])==1)
    {
        for(j=1;j<8;j++)
            scanf("%d",&r[j]);
        for(i=0,min=8;i<92 && min>0;i++)
        {
            for(j=k=0;j<8 && k<min;j++)
                k+=(r[j]!=s[i][j]);
            min<?=k;
        }
        printf("Case %d: %d\n",C++,min);
    }
    
}
