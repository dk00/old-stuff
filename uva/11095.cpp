#include<cstdio>
int n,s[100],c[50][50];
bool go(int d,int v)
{
    if(v>=n && d>=0)return 1;
    if(d<0)return 0;
    if(s[v]>=0)return go(d,v+1);
    for(int i=v+1;i<n;i++)
        if(c[v][i] && s[i]<0)
            s[i]=v,d--;
    if(go(d,v+1))
        return 1;
    for(int i=v+1;i<n;i++)
        if(c[v][i] && s[i]==v)
            s[i]=-1,d++;
    s[v]=v;
    if(go(d-1,v+1))
        return 1;
    s[v]=-1;
    return 0;
}
main()
{
    int i,j,m,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            for(j=0,s[i]=-1;j<n;j++)
                c[i][j]=0;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i][j]=c[j][i]=1;
        }
        for(i=0;!go(i,0) && i<=n;i++);
        printf("Case #%d: %d\n",C++,i);
        for(i=0;i<n;i++)
            if(s[i]>=0)printf("%d ",i);
        puts("");
    }
}
