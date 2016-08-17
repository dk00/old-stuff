#include<cstdio>
int n,min,u[13],dg[13],best[13],path[13],c[13][13];
int gcd(int a,int b)
{
    while((a%=b) && (b%=a));
    return a+b;
}
void go(int d,int v,int s,int rem)
{
    if(d>=n)
    {
        if(s<min)
        {
            min=s;
            for(d=1;d<n;d++)best[d]=path[d];
        }
        return;
    }
    for(int i=1;i<n;i++)
        if(u[i] && c[v][i]<100000)
        {
            path[d]=i;
            u[i]=0;
            go(d+1,i,s+c[v][i]*rem,rem-dg[i]);
            u[i]=1;
        }
}
main()
{
    int i,j,k,l,v,m,t,C=1;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            for(j=dg[i]=0;j<n;j++)
                c[i][j]=100000;
        scanf("%d",&v);
        for(l=0;l<m;l++)
        {
            scanf("%d %d %d",&i,&j,&k);
            c[i][j]=c[j][i]=k;
            c[i][i]=c[j][j]=0;
            dg[i]++,dg[j]++;
        }
        for(k=0;k<n;k++)
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    c[i][j]<?=(c[i][k]+c[k][j]);
        for(i=1;i<n;i++)u[i]=1;
        min=1000000000;
        go(1,0,0,m*2-dg[0]);
        for(i=1;i<n;i++)
            min+=dg[i]*c[0][i];
        printf("Case %d:\n",C++);
        printf("%d/%d\n",min/gcd(min,v*m*2),v*m*2/gcd(min,v*m*2));
        printf("0");
        for(i=1;i<n;i++)
            printf(" %d",best[i]);
        puts("");
        if(t)puts("");
    }
}
