#include<cstdio>
const int N=1001,inf=N;
bool p[N][N];
int un,u[N][N],g[N];
char x[N];
bool go(int s,int t)
{
    if(u[s][t]==un)return p[s][t];
    u[s][t]=un;
    if(s>=t)return p[s][t]=1;
    return p[s][t]=x[s]==x[t] && go(s+1,t-1);
}
main()
{
    int i,j,k,n,T;
    scanf("%d",&T);
    while(un++,T--){
        scanf("%s",x);
        for(i=0;x[i];i++)g[i+1]=inf;
        for(i=0;x[i];i++)
            for(j=0;x[i+j];j++)
                if(go(i,i+j))
                    g[i+j+1]<?=g[i]+1;
        printf("%d\n",g[i]);
    }
}
