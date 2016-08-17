#include<cstdio>
const int inf=200000;
char u[200];
int n,st,ed,min,next,p0[200],d0[200],q[256],d1[200],c[200][200];
void test()
{
    int i,j,k;
    for(k=0;k<n;k++)
        d0[k]=inf,u[k]=0;
    q[0]=ed,d0[ed]=0,u[ed]=1;
    for(i=0,j=1;i<j;i++)
    {
        u[q[i&255]]=0;
        for(k=0;k<n;k++)
            if(d0[q[i&255]]+c[q[i&255]][k]<d0[k])
            {
                d0[k]=d0[q[i&255]]+c[q[i&255]][k];
                if(!u[k])q[j++&255]=k;
            }
    }
    for(k=0;k<n;k++)u[k]=0;
}
char go(int v,int d=0)
{
    p0[d]=v;
    if(d1[d]+d0[v]>min)
    {
        next<?=(d1[d]+d0[v]);
        return 0;
    }
    if(v==ed)
    {
        int i,j,k;
        for(i=0,j=d;i<=j;)
        {
            k=(i+j)/2;
            if(d1[k]*2>d1[d])j=k-1;
            else if(d1[k]*2<d1[d])i=k+1;
            else return 1;
        }
        return 0;
    }
    
    char tmp;
    for(int i=0;i<n;i++)
        if(c[v][i]<inf && !u[i])
        {
            d1[d+1]=d1[d]+c[v][i];
            u[i]++;
            tmp=go(i,d+1);
            u[i]--;
            if(tmp)return 1;
        }
    return 0;
}
main()
{
    int i,j,k,m,C=1;
    while(scanf("%d %d %d %d",&n,&m,&st,&ed)==4 && n)
    {
        st--,ed--,min=inf;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=inf;
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            i--,j--;
            c[i][j]=c[j][i]=k;
        }
        next=inf,u[0]=1;
        test();
        for(min=d0[st];!go(st);min=next,next=inf);
        if(C>1)puts("");
        printf("Case %d: %d\n",C++,min/2);
        for(i=j=0;j*2<min;j+=c[p0[i]][p0[i+1]],i++);
        for(k=i;j<min;j+=c[p0[i]][p0[i+1]],i++);
        printf("%d",k+1);
        for(j=0;j<=k;j++)
            printf(" %d",p0[j]+1);
        printf("\n%d",n-k);
        for(;i>=k;i--)
            printf(" %d",p0[i]+1);
        puts("");
    }
}
