#include<cstdio>
int s,t,n,p[200],q[200],r[200],c[150][150];
int min(int a,int b){return a<b?a:b;}
int flow()
{
    int i,j,k,f=0;
    while(1){
        for(i=0;i<n;i++)
            p[i]=i;
        r[s]=200000000;
        q[0]=s;
        for(i=0,j=1;i<j && p[t]==t;i++)
            for(k=0;k<n;k++)
                if(p[k]==k && c[q[i]][k]>0)
                {
                    p[k]=q[i];
                    r[k]=min(c[q[i]][k],r[q[i]]);
                    q[j++]=k;
                }
        if(p[t]==t)
            break;
        for(k=t;k!=s;k=p[k])
        {
            c[k][p[k]]+=r[t];
            c[p[k]][k]-=r[t];
        }
        f+=r[t];
    }
    return f;
}
main()
{
    int i,j,k,m,C=1;
    while(scanf("%d",&n)==1 && n)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=0;
        scanf("%d %d %d",&s,&t,&m);
        s--,t--;
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            c[i-1][j-1]+=k;
            c[j-1][i-1]+=k;
        }
        printf("Network %d\nThe bandwidth is %d.\n\n",C++,flow());
    }
}
