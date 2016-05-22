#include<cstdio>
int n,b[13],u[13],dg[13],c[13][13];
int p[8192][13],s[8192][13];
int gcd(int a,int b)
{
    while((a%=b) && (b%=a));
    return a+b;
}
int go(int d,int v,int rem)
{
    if(p[d][v]>=0)
        return s[d][v];
    s[d][v]=10000000;
    int now;
    for(int i=1;i<n;i++)
        if(d&b[i] && i!=v)
        {
            now=go(d&~b[v],i,rem+dg[i])+c[i][v]*rem;
            if(now<s[d][v])
            {
                p[d][v]=i;
                s[d][v]=now;
            }
        }
    return s[d][v];
}
void print(int j,int k)
{
    if(j==1 || k==0)
        printf("0");
    else
    {
        print(j&~b[k],p[j][k]);
        printf(" %d",k);
    }
}
main()
{
    int i,j,k,l,v,m,t,min,C=1;
    for(b[0]=i=1;i<13;i++)
        b[i]=b[i-1]<<1;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
        {
            for(j=dg[i]=0;j<n;j++)
                c[i][j]=100000;
            for(j=0;j<8192;j++)
                p[j][i]=-1;
        }
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
        for(i=j=0;i<n;i++)
        {
            j=j*2+1;
            p[1|b[i]][i]=0,
            s[1|b[i]][i]=c[0][i]*(m*2-dg[0]);
        }
        for(i=1;i<n;i++)
        {
            l=go(j,i,dg[i]);
            if(l<min)min=l,k=i;
        }
        for(i=1;i<n;i++)
            min+=dg[i]*c[0][i];
        printf("Case %d:\n",C++);
        printf("%d/%d\n",min/gcd(min,v*m*2),v*m*2/gcd(min,v*m*2));
        print(j,k);
        puts("");
        if(t)puts("");
    }
}
