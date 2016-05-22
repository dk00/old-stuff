#include<cstdio>
int s[501][501],to[250001];
main()
{
    int i,j,k,n,m;
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=k=0;i<n;i++)
            for(j=0;j<n;j++)
                s[i][j]=k++;
        for(i=k=0;i<n*2-1;i++)
            for(j=0>?(i-n+1);j<=i && j<n;j++)
                to[s[j][i-j]]=k++;
        for(i=to[m-1],j=1;i!=m-1;i=to[i],j++);
        scanf("%d",&k);
        k%=j;
        for(i=m-1;k--;i=to[i]);
        printf("%d\n",i+1);
    }
}
