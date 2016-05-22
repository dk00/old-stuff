#include<cstdio>
const long long D=100000000000000000ll,num[]={6,2,5,5,4,5,6,3,7,8};
char __tmp[1000];
int u,m,v[3001],p[3001],q[303000];
class midint
{
public:
    int n,o;
    long long s[3];
    midint(){o=n=s[0]=s[1]=s[2]=0;}
    bool operator<(midint a)
    {
        if(n!=a.n)return n<a.n;
        if(n>2 && s[2]!=a.s[2])return s[2]<a.s[2];
        if(n>1 && s[1]!=a.s[1])return s[1]<a.s[1];
        return s[0]<a.s[0];
    }
    void operator+=(int x)
    {
        o=o*10%m;
        s[0]*=10,s[1]*=10,s[2]*=10,s[0]+=x;
        s[1]+=s[0]/D,s[0]%=D;
        s[2]+=s[1]/D,s[1]%=D;
        if(s[2])n=3;
        else if(s[1])n=2;
        else n=1;
    }
    char *tostr()
    {
        if(n==3)sprintf(__tmp,"%I64d %I64d %I64d(%d)",s[2],s[1],s[0],o);
        if(n==2)sprintf(__tmp,"%I64d %I64d(%d)",s[1],s[0],o);
        if(n==1)sprintf(__tmp,"%I64d(%d)",s[0],o);
        if(n<1)sprintf(__tmp,"-1");
        return __tmp;
    }
}*s[101][3000],zero;
midint go(int n,int x)
{
    if(n==0 && x==0)return zero;
    if(s[n][x])return *s[n][x];
    midint now,max;
    for(int i=0;i<10;i++)
    {
        if(n<num[i])continue;
        for(int j=p[(x+m-i%m)%m];j<p[(x+m-i%m)%m+1];j++)
        {
            now=go(n-num[i],v[j]);
            if(!now.n)break;
            now+=i;
            if(max<now)max=now;
        }
    }
    s[n][x]=new midint;
    q[u++]=n*m+x;
    return(*s[n][x]=max);
}
main()
{
    zero.n=1,zero.s[0]=0;
    int i,n;
    while(scanf("%d %d",&n,&m)==2 && n)
    {
        u=0;
        for(i=0;i<=m;i++)p[i]=q[i]=0;
        for(i=0;i<m;i++)p[i*10%m+1]++;
        for(i=0;i<m;i++)p[i+1]+=p[i];
        for(i=0;i<m;i++)v[p[i*10%m]+q[i*10%m]++]=i;
        /*for(i=0;i<19;i++)
        {
            printf("%d:",i);
            for(int j=p[i];j<p[i+1];j++)
                printf(" %d",v[j]);
            puts("");
        }*/
        puts(go(n,0).tostr());
        while(u--)
        {
            delete s[q[u]/m][q[u]%m];
            s[q[u]/m][q[u]%m]=0;
        }
    }
}
