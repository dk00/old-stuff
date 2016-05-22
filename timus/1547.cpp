#include<cstdio>
struct pw
{
    short n,s[55];
    void operator+=(pw a)
    {
        for(;n<a.n;n++)s[n]=0;
        for(;a.n<n;a.n++)a.s[a.n]=0;
        s[n]=a.s[n]=0;
        for(int i=0;i<n;i++)
        {
            s[i]+=a.s[i];
            s[i+1]+=s[i]/26;
            s[i]%=26;
        }
        if(s[n]>0)n++;
    }
    void operator-=(pw a)
    {
        for(i=a.n-1;i>=0;i--)
            s[i]-=a.s[i];
        for(i=0;i<n;i++)
            if(s[i]<0)
                s[i+1]--,s[i]+=25;
        while(n>0 && s[n-1]==0)n--;
    }
    void operator--()
    {
        s[0]--;
        for(int i=0;s[i]==-1;i++)
            s[i+1]--,s[i]=25;
        if(s[n-1]==0)n--;
    }
    void operator++()
    {
        s[0]++,s[n]=0;
        for(int i=0;s[i]==26;i++)
            s[i+1]++,s[i]=0;
        if(s[n])n++;
    }
    short operator/=(short x)
    {
        for(int i=n-1;i>0;i--)
        {
            s[i-1]+=s[i]%x*26;
            s[i]/=x;
        }
        short tmp=s[0]%x;
        s[0]/=x;
        while(n>0 && s[n-1]==0)n--;
        return tmp;
    }
    void print()
    {
        for(int i=n-1;i>=0;i--)
            putchar(s[i]+'a');
    }
};
main()
{
    int i,j,n,m;
    pw tmp,one,sum;
    while(scanf("%d %d",&n,&m)==2)
    {
        one.n=one.s[0]=one.s[1]=0;
        for(i=1;i<=n;i++)
        {
            for(j=0;j<i;j++)
                tmp.s[j]=25;
            tmp.n=j;
            one+=tmp;
        }
        n=(one/=m);
        --one;
        sum.n=1,sum.s[0]=sum.s[1]=0;
        for(i=0;i<m;i++)
        {
            sum.print();
            putchar('-');
            sum+=one;
            if(i<n)++sum;
            sum.print();
            puts("");
            ++sum;
        }
    }
}
