#include<cstdio>
#include<cstring> 
int t,p[100],c[100][100]; //VC T-shirt
int go(int v)
{
    if(v==t)return 1;
    if(p[v])return 0;
    p[v]=1;
    for(int i=1;i<=t;i++)
        if(c[v][i])
        {
            c[v][i]--;
            if(go(i))
            {
                c[i][v]++;
                return 1;
            }
            c[v][i]++;
        }
    return 0;
}
int flow()
{
    int i,sum=0;
    while(1)
    {
        for(i=0;i<=t;i++)
            p[i]=0;
        if(go(0))sum++;
        else break;
    }
    return sum;
}
int size(char *tmp)
{
    if(!stricmp(tmp,"XXL"))return 1;
    if(!stricmp(tmp,"XL"))return 2;
    if(!stricmp(tmp,"L"))return 3;
    if(!stricmp(tmp,"M"))return 4;
    if(!stricmp(tmp,"S"))return 5;
    if(!stricmp(tmp,"XS"))return 6;
}
main()
{
    int i,j,n,m,T;
    char tmp[1000];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        t=m+6+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                c[i][j]=0;
        for(i=m+1;i<=m+6;i++)
            c[i][t]=n/6;
        for(i=1;i<=m;i++)
        {
            scanf("%s",tmp);
            c[0][i]=c[i][m+size(tmp)]=1;
            scanf("%s",tmp);
            c[i][m+size(tmp)]=1;
        }
        if(flow()>=m)
            puts("YES");
        else
            puts("NO");
    }
}
