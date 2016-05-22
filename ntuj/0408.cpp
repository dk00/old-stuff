#include<cstdio>
#include<cstring>
int test(int x)
{
    int l=0;
    while(x)
    {
        if(l&(x%2))return 0;
        l=x%2;
        x/=2;
    }
    return 1;
}
const int N=9999,M=100000000;
int u[N],s0[N],s1[N];
main()
{
    int i,j,k,n,m,x;
    for(i=0;i<4096;i++)
        u[i]=test(i);
    while(~scanf("%d %d",&n,&m))
    {
        memset(s0,0,sizeof(s0));
        memset(s1,0,sizeof(s1));
        s0[0]=1;
        for(i=0;i<n;i++)
        {
            for(j=x=0;j<m;j++)
                scanf("%d",&k),x=x*2+k;
            for(j=(1<<m)-1;j>=0;j--)
                for(k=(1<<m)-1;k>=0;k--)
                    if(!(j&k) && (k&x)==k && u[k])
                        s1[k]=(s1[k]+s0[j])%M;
            memcpy(s0,s1,sizeof(s0));
            memset(s1,0,sizeof(s1));
        }
        for(j=0,i=(1<<m)-1;i>=0;i--)
            j=(j+s0[i])%M;
        printf("%d\n",j);
    }
}
