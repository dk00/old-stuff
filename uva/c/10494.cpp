#include<cstdio>
char op[2],tmp[100000],ans[100000];
main()
{
    int i;
    long long n,m;
    while(scanf("%s %s %lld",tmp,op,&n)==3)
    {
        for(i=0,m=0;tmp[i];i++)
        {
            m=m*10+tmp[i]-'0';
            ans[i]=m/n+'0';
            m%=n;
        }
        ans[i]=0;
        if(op[0]=='/')
        {
            for(i=0;ans[i]=='0' && ans[i+1];i++);
            puts(ans+i);
        }
        else
            printf("%lld\n",m);
    }
}
