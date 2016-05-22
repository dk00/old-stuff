/*
LANG:C++
TASK:telewire
*/
#include<cstdio>
long long inf=20000000000ll;
inline int sq(int x){return x*x;}
int h[100000];
long long s[2][101],tmp,*s1,*s2;
long long abs(long long a){return a<0?-a:a;}
main()
{
    freopen("telewire.in","r",stdin);
    freopen("telewire.out","w",stdout);
    int i,j,k,c,n,m;
    while(scanf("%d %d",&n,&c)==2)
    {
        for(i=m=0;i<n;i++)
        {
            scanf("%d",h+i);
            if(h[i]>m)m=h[i];
        }
        for(j=0;j<=m;j++)
            s[1][j]=inf;
        for(j=0;j<h[i];j++)
            s[0][j]=inf;
        for(;j<=m;j++)
            s[0][j]=sq(h[0]-j);
        for(i=1;i<n;i++)
        {
            s1=s[1-i%2];
            s2=s[i%2];
            for(j=0;j<=m;j++)s2[j]=inf;
            for(j=h[i];j<=m;j++)
                for(k=h[i-1];k<=m;k++)
                {
                    tmp=s1[k]+c*abs(j-k)+sq(h[i]-j);
                    if(tmp<s2[j])s2[j]=tmp;
                }
        }
        tmp=s2[h[n-1]];
        for(j=h[n-1];j<=m;j++)
            if(s2[j]<tmp)
                tmp=s2[j];
        printf("%lld\n",1ll*tmp);
    }
}
