#include<set>
#include<cstdio>
#include<algorithm>
struct pa
{
    int b,n,ui;
    bool operator<(pa a)const
    {
        return(b<a.b ||(b<=a.b && n<a.n));
    }
};
int n,d,br,use[20],r[20],s[20],num1[30241];
int _p,cnt1,cnt2;
void pre(std::set<pa>& s0,int v,int num)
{
    if(v<n/2)
    {
        cnt1++;
        std::set<pa>::iterator p;
        p=s0.find((pa){br,num,0});
        if(p==s0.end())
            s0.insert((pa){br,num,_p++});
        else num1[s0.find((pa){br,num,0})->ui]++;
        return;
    }
    int i,last;
    for(i=n-1;i>=0;i--)
        if(use[i] && s[i]!=last)
        {
            use[i]--;
            br|=(1<<i);
            last=s[i];
            pre(s0,v-1,(num+(r[v]*s[i])%d)%d);
            br&=~(1<<i);
            use[i]++;
        }
}
int go(std::set<pa>& s0,int v,int num)
{
    if(v<0)
    {
        cnt2++;
        std::set<pa>::iterator p;
        p=s0.find((pa){((1<<n)-1)^br,(d-num)%d});
        if(p==s0.end())
            return 0;
        return num1[p->ui];
    }
    int i,last,sum=0;
    for(i=0;i<n;i++)
        if(use[i] && s[i]!=last)
        {
            use[i]--;
            br|=(1<<i);
            last=s[i];
            sum+=go(s0,v-1,(num+(r[v]*s[i])%d)%d);
            br&=~(1<<i);
            use[i]++;
        }
    return sum;
}
main()
{
    int i,j,T;
    char tmp[100];
    std::set<pa> s0;
    scanf("%d",&T);
    while(T--)
    {
        s0.clear();
        scanf("%s %d",tmp,&d);
        for(n=0,r[0]=1%d;tmp[n];n++)
        {
            s[n]=tmp[n]-'0';
            r[n+1]=(r[n]*10)%d;
            use[n]=1;
        }
        std::sort(s,s+n);
        std::fill(num1,num1+30240,1);
        cnt1=cnt2=0;
        pre(s0,n-1,0);
        printf("%d\n",go(s0,n/2-1,0));
        printf("%d %d\n",cnt1,cnt2);
    }
}
