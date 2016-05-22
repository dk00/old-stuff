#include<cstdio>
#define scanf ~scanf
const int inf=2000000000;
struct pt{int v,f;}q[100001];
int f[101][101],c[101][101],d[101][101],u[101];
main()
{
    char tmp[9];
    sscanf(tmp,"");
    int i,j,k,n,m,t,nv,nf;
    while(scanf("%d %d %d %d",&n,&m,&q[0].v,&t))
    {
        for(i=0;i<n;i++)
            for(j=0,u[i]=1;j<=100;j++)
                c[i][j]=d[i][j]=inf;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            scanf("%d %d",&c[i-1][j-1],&f[i-1][j-1]);
        }
        d[q[0].v][0]=0;
        for(i=0,j=1;i<j;i++)
        {
            u[nv=q[i].v]=1,nf=q[i].f;
            for(k=0;k<n;k++)
                if(c[nv][k]<inf && d[nv][nf]+c[nv][k]<d[k][nf+f[nv][k]])
                {
                    d[k][nf+f[nv][k]]=d[nv][nf]+c[nv][k];
                    if(u[k])
                        u[k]=0,q[j++]=(pt){k,nf+f[nv][k]};
                }
        }
        
    }
}
