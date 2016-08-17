#include<cstdio>
int n,p,p1,p2,s[1000],
a0[100][100],a1[100][100],b0[100][100],b1[100][100];
int sum(int a,int b)
{
    if(a)
        return s[b]-s[a-1];
    return s[b];
}
int go(int st,int ed,int alpha,int beta)
{
    if(st>ed)
        return p1-p2;
    int i,tmp;
    if(p==0)
    {
        if(a1[st][ed])
            return a0[st][ed];
        for(i=st;i<=ed;i++)
        {
            p=!p,p1+=sum(st,i);
            tmp=go(i+1,ed,alpha,beta);
            p=!p,p1-=sum(st,i);
            if(tmp>alpha)
                alpha=tmp;
            if(alpha>=beta)
                return alpha;
            p=!p,p1+=sum(i,ed);
            tmp=go(st,i-1,alpha,beta);
            p=!p,p1-=sum(i,ed);
            if(tmp>alpha)
                alpha=tmp;
            if(alpha>=beta)
                return alpha;
        }
        a0[st][ed]=alpha,a1[st][ed]=1;
        return alpha;
    }
    else
    {
        if(b1[st][ed])
            return b0[st][ed];
        for(i=st;i<=ed;i++)
        {
            p=!p,p2+=sum(st,i);
            tmp=go(i+1,ed,alpha,beta);
            p=!p,p2-=sum(st,i);
            if(tmp<beta)
                beta=tmp;
            if(alpha>=beta)
                return beta;
            p=!p,p2+=sum(i,ed);
            tmp=go(st,i-1,alpha,beta);
            p=!p,p2-=sum(i,ed);
            if(tmp<beta)
                beta=tmp;
            if(alpha>=beta)
                return beta;
        }
        b0[st][ed]=beta,b1[st][ed]=1;
        return beta;
    }
}
main()
{
    int i,j;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);
        for(i=1;i<n;i++)
            s[i]+=s[i-1];
        for(i=0;i<n;i++)
            for(j=i;j<n;j++)
                a1[i][j]=b1[i][j]=0;
        p=p1=p2=0;
        printf("%d\n",go(0,n-1,-200000000,200000000));
    }
}
