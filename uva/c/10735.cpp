#include<cstdio>
#include<cstdlib>
int n,t,dg[102],p[102],q[102],c[102][102],o[102][102],r[102][102];
int flow()
{
    int i,j,k,f=0,s=0;
    while(1)
    {
        for(i=0;i<n;i++)p[i]=i;
        p[s]=-1,q[0]=s;
        for(i=0,j=1;i<j;i++)
            for(k=0;k<n;k++)
                if(p[k]==k && c[q[i]][k])
                    q[j++]=k,p[k]=q[i];
        if(p[t]==t)break;
        for(i=t;i!=s;i=p[i])
            c[p[i]][i]--,c[i][p[i]]++;
        f++;
    }
    return f;
}
void go(int v)
{
    for(int i=1;i<t;i++)
        if(c[v][i])
            c[v][i]--,c[i][v]--,go(i);
    for(int i=1;i<t;i++)
        if(o[v][i])
            o[v][i]--,go(i);
    if(p[0]++)putchar(' ');
    printf("%d",v);
}
main()
{
    char tmp[10];
    int i,j,k,m,T,C=0;
    scanf("%d",&T);
    while(T--)
    {
        if(C++)puts("");
        scanf("%d %d",&n,&m);
        t=n+1,n+=2;
        for(i=0;i<=t;i++)
            for(j=dg[i]=0;j<=t;j++)
                o[i][j]=c[i][j]=0;
        while(m--)
        {
            scanf("%d %d %s",&i,&j,tmp);
            if(tmp[0]=='U')
                c[i][j]++,c[j][i]++;
            else o[j][i]++,dg[j]--,dg[i]++;
        }
        for(i=1,k=0;i<t;i++)
            if(dg[i]<0)c[0][i]=-dg[i];
            else if(dg[i]>0)c[i][t]=dg[i],k+=dg[i];
        for(i=1;i<t;i++)
            for(j=1;j<t;j++)
                r[i][j]=c[i][j];
        if(flow()<k)
        {
            puts("No euler circuit exist");
            continue;
        }
        for(i=1;i<t;i++)
            for(j=1;j<t;j++)
            {
                if(c[i][j]>(c[i][j]+c[j][i])/2)
                    o[i][j]+=c[i][j]-(c[i][j]+c[j][i])/2;
                c[i][j]=r[i][j]-abs(c[i][j]-r[i][j]);
            }
        p[0]=0,go(1);
        puts("");
    }
}
