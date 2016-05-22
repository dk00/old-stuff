#include<cstdio>
int n,dx[]={1,1,2,2},dy[]={2,-2,1,-1};
int pn,u[20][6],path[20][2],tmp[69][4];
int s[2][69],c[69][69],c1[69][69],c2[69][69];
int go(int d)
{
    if(d>=n)
    {
        if(n==2)
        {
            tmp[pn][0]=path[0][0],tmp[pn][1]=path[0][1];
            tmp[pn][2]=path[1][0],tmp[pn][3]=path[1][1];
            pn++;
        }
        if(n==3)
        {
            int s1,s2;
            for(s1=0;;s1++)
                if(tmp[s1][0]==path[0][0] && tmp[s1][1]==path[0][1]
                && tmp[s1][2]==path[1][0] && tmp[s1][3]==path[1][1])
                    break;
            for(s2=0;;s2++)
                if(tmp[s2][0]==path[1][0] && tmp[s2][1]==path[1][1]
                && tmp[s2][2]==path[2][0] && tmp[s2][3]==path[2][1])
                    break;
            c[s1][s2]=1;
        }
        return 1;
    }
    int i,j,k,sum=0;
    for(i=0;i<6;i++)
        if(!u[d][i])
            for(j=i+1;j<6;j++)
                if(!u[d][j])
                {
                    for(k=0;k<4;k++)
                    {
                        if(i+dy[k]>=0 && i+dy[k]<6)
                            u[d+dx[k]][i+dy[k]]++;
                        if(j+dy[k]>=0 && j+dy[k]<6)
                            u[d+dx[k]][j+dy[k]]++;
                    }
                    path[d][0]=i,path[d][1]=j;
                    sum+=go(d+1);
                    for(k=0;k<4;k++)
                    {
                        if(i+dy[k]>=0 && i+dy[k]<6)
                            u[d+dx[k]][i+dy[k]]--;
                        if(j+dy[k]>=0 && j+dy[k]<6)
                            u[d+dx[k]][j+dy[k]]--;
                    }
                }
    return sum;
}
int go()
{
    if(n==1)return 15;
    if(n==2)return 69;
    n-=2;
    const int M=10007;
    int i,j,k,l,p=0;
    for(j=0;j<69;j++)
    {
        s[0][j]=1;
        for(k=0;k<69;k++)
            c1[j][k]=c[j][k];
    }
    for(i=1;i<=n && i>0;i*=2)
    {
        if(i&n)
        {
            for(j=0;j<69;j++)
                s[1][j]=s[0][j],s[0][j]=0;
            for(j=0;j<69;j++)
                for(k=0;k<69;k++)
                    s[0][k]=(s[0][k]+s[1][j]*c1[j][k])%M;
        }
        for(j=0;j<69;j++)
            for(k=0;k<69;k++)
                c2[j][k]=c1[j][k],c1[j][k]=0;
        for(l=0;l<69;l++)
            for(j=0;j<69;j++)
                for(k=0;k<69;k++)
                    c1[j][k]=(c1[j][k]+c2[j][l]*c2[l][k])%M;
    }
    for(j=k=0;j<69;j++)
        k=(k+s[0][j])%M;
    return k;
}
main()
{
    n=2,go(0);
    n=3,go(0);
    int i,j,T;
    scanf("%d",&T);
    while(T--)
        scanf("%d",&n),printf("%d\n",go());
}
