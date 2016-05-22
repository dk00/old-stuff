#include<cstdio>
struct Q
{
    int x,y,n;
}q[562145];
int s[513][513],p[135537];
char t[562145];
const int rr[]={0,0,1,1},ll[]={0,1,0,1};
int sum(int x1,int y1,int x2,int y2)
{
    return s[x1-1][y1-1]+s[x2][y2]-s[x1-1][y2]-s[x2][y1-1];
}
main()
{
    int i,j,k,l,x,y,tmp,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
            {
                scanf("%d",&s[i][j]);
                s[i][j]+=s[i][j-1];
            }
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                s[i][j]+=s[i-1][j];
        q[j=l=0]=(Q){1,1,n/2};
        tmp=s[n][n];
        if(tmp==0 || tmp==n*n)
            t[l++]=0,t[l++]=(tmp>0);
        else j=1,t[l++]=1;
        for(i=0;i<j;i++)
        {
            x=q[i].x,y=q[i].y,n=q[i].n;
            for(k=0;k<4;k++)
            {
                tmp=sum(x+n*rr[k],y+n*ll[k],x+n*rr[k]+n-1,y+n*ll[k]+n-1);
                if(tmp==0 || tmp==n*n)
                    t[l++]=0,t[l++]=(tmp>0);
                else
                {
                    t[l++]=1;
                    if(n/2)q[j++]=(Q){x+n*rr[k],y+n*ll[k],n/2};
                }
            }
        }
        for(i=0;l--;i++)
        {
            if(i%4==0)p[i/4]=0;
            if(t[l])p[i/4]|=1<<(i%4);
        }
        i=(i-1)/4+1;
        while(i--)printf("%X",p[i]);
        puts("");
    }
}
