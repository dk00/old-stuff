#include<cstdio>
struct A
{
    int n,s[100][100];
    void get(int _n)
    {
        n=_n;
        int i,j;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                scanf("%d",&s[i][j]);
    }
    void operator*=(A t)
    {
        int i,j,k,tmp[100][100];
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                tmp[i][j]=-1;
        for(k=0;k<n;k++)
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    if(s[i][k]>=0 && t.s[k][j]>=0)
                        tmp[i][j]>?=(s[i][k]+t.s[k][j]);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                s[i][j]=tmp[i][j];
    }
};
main()
{
    int i,n,st,ed,m,max;
    A j,k;
    while(scanf("%d %d %d %d",&n,&st,&ed,&m) && n+st+ed+m)
    {
        max=0;
        j.get(n);
        for(i=1;!(i&m);i*=2,j*=j);
        k=j;
        for(i*=2,j*=j;i<=m;i*=2,j*=j)
            if(i&m)
                k*=j;
        while(ed--)
        {
            scanf("%d",&i);
            max>?=k.s[st-1][i-1];
        }
        printf("%d\n",max);
    }
}
