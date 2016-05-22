#include<cstdio>
#include<cstring>
const int N=11,M=10001;
struct cy
{
    int st,m,s[M];
    int& operator[](int n)
    {
        if(n>st)
            n=st+(n-st)%m;
        return s[n];
    }
    void print()
    {
        for(int i=0;i<st+m;i++)
            printf(" %d",s[i]);
        puts("");
    }
}z[2][N];
int a,C=1;
int p[M],val[M],ref[M];
cy &init(int n,int st,int m)
{
    int i;
    if(n==0)
    {
        cy &val=z[1][0];
        val.st=0,val.m=m;
        for(i=0;i<st+m;i++)
            val[i]=i+1;
        val[st+m-1]=st;
        return val;
    }
    cy &pval=(z[0][n-1]=init(n-1,st,m));
    init(n-1,pval.st,pval.m);
    cy &pref=z[1][n-1];
    memset(p,-1,sizeof(p));
    if(n==1)val[0]=ref[0]=a;
    if(n==2)val[0]=ref[0]=0;
    if(n>=3)val[0]=ref[0]=1;
    for(i=0;p[val[i]]<0;i++)
    {
        p[val[i]]=i;
        ref[i+1]=pref[ref[i]];
        val[i+1]=pval[ref[i]];
    }
    cy &r=z[1][n];
    r.st=p[val[i]],r.m=i-p[val[i]];
    memcpy(r.s,val,sizeof(r.s));
    /*printf("(%2d:%2d,%2d)",n,st,m);
    r.print();*/
    return r;
}
main()
{
    int T,n,m,b;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d %d",&m,&n,&a,&b);
        printf("Case #%d: %d\n",C++,init(n,0,m)[b]);
    }
}
