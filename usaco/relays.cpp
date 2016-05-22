/*
TASK:relays
LANG:C++
*/
#include<cstdio>
const int inf=1000000000;
int n;
void copy(int c1[101][101],int c2[101][101])
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c1[i][j]=c2[i][j];
}
void add(int c0[101][101],int c1[101][101],int c2[101][101])
{
    int i,j,k,tmp;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c0[i][j]=inf;
    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if((tmp=c1[i][k]+c2[k][j])<c0[i][j])
                    c0[i][j]=tmp;
}
int u[1001],a[101][101],c[101][101],d[101][101];
main()
{
    freopen("relays.in","r",stdin);
    freopen("relays.out","w",stdout);
    int i,j,k,m,C,st,ed;
    while(scanf("%d %d %d %d",&C,&m,&st,&ed)==4)
    {
        for(i=0;i<101;i++)
            for(j=0;j<101;j++)
                c[i][j]=a[i][j]=inf;
        for(i=n=0;i<1000;i++)u[i]=-1;
        while(m--)
        {
            scanf("%d %d %d",&k,&i,&j);
            if(u[--i]<0)u[i]=n++;
            if(u[--j]<0)u[j]=n++;
            i=u[i],j=u[j];
            c[i][j]=c[j][i]=k;
        }
        for(i=0;i<n;i++)
            a[i][i]=0;
        for(i=1;i<=C;i*=2)
        {
            if(C&i)
            {
                copy(d,a);
                add(a,c,d);
            }
            copy(d,c);
            add(c,d,d);
        }
        printf("%d\n",a[u[st-1]][u[ed-1]]);
    }
}


