#include<cstdio>
bool notp[101];
main()
{
    int i,j,n,m,pn,p[100],num[100];
    long long k;
    p[0]=2,pn=1;
    for(i=3;i<100;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*i;j<100;j+=i*2)notp[j]=1;
        p[pn++]=i;
    }
    while(scanf("%d %d",&n,&m) &&(n!=0 || m!=0))
    {
        if(m==0)
        {
            puts("-");
            continue;
        }
        for(j=0;j<pn;j++)
            num[j]=0;
        for(j=0;j<pn;j++)
            for(i=n/p[j];i>0;i/=p[j])
                num[j]+=i;
        for(j=0;j<pn;j++)
            while(m%p[j]==0)
                m/=p[j],num[j]--;
        if(m>100 || m<-100)
        {
            puts("0");
            continue;
        }
        for(j=0,k=1;j<pn;j++)
            k*=((num[j]+1)>?0);
        printf("%lld\n",k);
    }
}
