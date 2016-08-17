#include<cstdio>
#include<algorithm>
int n,d,use,num,r[11];
char s[100];
void add(int i,int x)
{
    use|=(1<<i);
    num=(num+r[x]*s[i])%d;
}
void sub(int i,int x)
{
    use&=~(1<<i);
    num=(num+(d-s[i])*r[x])%d;
}
int calc(int x)
{
    if(x<0 && !num)
        return 1;
    int i,sum,last=-1;
    for(i=sum=0;i<n;i++)
        if(s[i]!=last && !(use&(1<<i)))
        {
            add(i,x);
            last=s[i];
            sum+=calc(x-1);
            sub(i,x);
        }
    return sum;
}
main()
{
    int i,t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s %d",s,&d);
        for(n=0;s[n];n++);
        std::sort(s,s+n);
        for(i=0,r[0]=1;i<n;i++)
        {
            r[i+1]=(r[i]*10)%d;
            s[i]-='0';
        }
        printf("%d\n",calc(n-1));
    }
}
