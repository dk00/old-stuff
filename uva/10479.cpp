#include<cstdio>
main()
{
    int i,j,m,pre;
    long unsigned long k,n;
    while(scanf("%llu",&n)==1 && n)
    {
        for(m=k=1;k<n;m++,k*=2);
        n-=k/2;
        for(i=0,pre=-1;i<m;i++)
        {
            for(j=0;n>(1ll<<((m-i-2)>?0)) && j<pre;j++)
                n-=(1ll<<((m-i-2)>?0));
            if(j<pre)pre=0;
            else pre++;
        }
        printf("%d\n",pre);
    }
}
