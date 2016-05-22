#include<cstdio>
int n,u1[2008],u2[2008];
char c[2008][2008],s1[2008],s2[2008];
int go(int v,int x,int u[])
{
    if(u[v] && u[v]!=x+1)return -1;
    if(u[v])return 0;
    u[v]=x+1;
    int i,j,sum=x;
    for(i=0;i<n;i++)
        if(c[v][i])
        {
            j=go(i,!x,u);
            if(j<0)return -1;
            sum+=j;
        }
    return sum;
}
main()
{
    int i,j,k,n1,n2,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&n1,&n2,&m);
        n=n1+n2;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=0;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            i--,j--;
            c[i][j]=c[j][i]=1;
        }
        for(i=0;i<n;i++)u1[i]=u2[i]=s1[i]=s2[i]=0;
        s1[0]=1;
        for(i=0;i<n;i++)
        {
            if(u1[i] || u2[i])continue;
            m=go(i,0,u1);
            k=go(i,1,u2);
            if(m<0 || k<0)break;
            for(j=n1;j>=m;j--)
                if(s1[j-m])s2[j]=1;
            for(j=n1;j>=k;j--)
                if(s1[j-k])s2[j]=1;
            for(j=0;j<=n1;j++)
                s1[j]=s2[j],s2[j]=0;
        }
        if(m>=0 && k>=0 && s1[n1])puts("yes");
        else puts("no");
    }
}
