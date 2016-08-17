#include<cstdio>
const int inf=2147483647;
int n,sum,d[20],c[20][20],o[20][20],p[20][20];
void fw()
{
    int i,j,k;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=o[i][j],p[i][j]=-1;
    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(c[i][k]<inf && c[k][j]<inf && c[i][k]+c[k][j]<c[i][j])
                    c[i][j]=c[i][k]+c[k][j],p[i][j]=k;
}
void go(int i,int j)
{
    if(p[i][j]<0)
    {
        if(o[i][j]<0)o[i][j]=o[j][i]=-o[i][j];
        else o[j][i]=-o[j][i],o[i][j]=inf;
        return;
    }
    go(i,p[i][j]);
    go(p[i][j],j);
}
void go()
{
    int i,j,a,b,min;
    while(1)
    {
        for(i=0;d[i]%2==0 && i<n;i++);
        if(i>=n)break;
        fw();
        min=inf;
        for(i=0;i<n;i++)
            for(j=i+1;j<n;j++)
                if(d[i]%2==1 && d[j]%2==1 && c[i][j]<min)
                    min=c[i][j],a=i,b=j;
        go(a,b);
        d[a]++,d[b]++;
        sum+=min;
    }
}
main()
{
    int i,j,k,m;
    while(scanf("%d %d",&n,&m) && n)
    {
        for(i=sum=0;i<n;i++)
            for(j=d[i]=0;j<n;j++)
                o[i][j]=inf;
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            i--,j--;
            o[i][j]<?=k,o[j][i]<?=k;
            d[i]++,d[j]++,sum+=k;
        }
        go();
        printf("%d\n",sum);
    }
}
