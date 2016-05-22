#include<cstdio>
const int inf=20000;
char u[300];
int n,n1,n2,st,ed,min,d0[300],q[300],ne[300][300],
    d1[300],p0[300],p1[300],p2[300],c[300][300];
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
void go(int v,int d=0)
{
    p0[d]=v;
    if(d1[d]+d0[v]>=min)return;
    if(v==ed)
    {
        int i,j,k;
        for(i=0,j=d;i<=j;)
        {
            k=(i+j)/2;
            if(d1[k]*2>d1[d])j=k-1;
            else if(d1[k]*2<d1[d])i=k+1;
            else break;
        }
        if(i<=j && d1[k]*2==d1[d])
        {
            min=d1[d];
            n1=n2=0;
            for(i=0;i<=k;i++)
                p1[n1++]=p0[i];
            for(i=d;i>=k;i--)
                p2[n2++]=p0[i];
        }
        return;
    }
    for(int i=0;i<n;i=ne[v][i])
        if(c[v][i]<inf && !u[i])
        {
            u[i]++;
            d1[d+1]=d1[d]+c[v][i];
            go(i,d+1);
            u[i]--;
        }
}
main()
{
    int i,j,k,m,C=1;
    while(scanf("%d %d %d %d",&n,&m,&st,&ed)==4 && n)
    {
        st--,ed--;
        for(i=0;i<n;i++)u[i]=0;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=inf;
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            i--,j--;
            c[i][j]=c[j][i]=k;
        }
        for(i=0;i<n;i++)
        {
            for(j=k=0;j<n;j++)
                if(c[i][j]<inf)
                    while(k<j)ne[i][k++]=j;
            while(k<n)ne[i][k++]=n;
        }
        test();
        min=inf,u[st]=1,go(st);
        printf("Case %d: %d\n",C++,min/2);
        printf("%d",n1);
        for(i=0;i<n1;i++)
            printf(" %d",p1[i]+1);
        printf("\n%d",n2);
        for(i=0;i<n2;i++)
            printf(" %d",p2[i]+1);
        puts("");
    }
}
