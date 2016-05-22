#include<cstdio>
#include<cmath>
int n,s[4],x[26];
char suit[]="shcd",nu[]="A23456789TJQK";
struct hand
{
    int h,c;
    hand(){}
    hand(int a,int b){h=a,c=b;}
}s0[2600000];
inline void test(int h)
{
    char k=0,f=0,S=0,t=0,tp=0,p=0;
    int i,j;
    for(i=0;i<13;i++)
    {
        if(x[i]==4)k=1;
        if(x[i]==3)t=1;
        if(x[i]==2)
        {
            if(!p)p=1;
            else tp=1;
        }
        x[i+13]=x[i];
    }
    for(i=0;i<4;i++)
        if(s[i]==5)f=1;
    for(i=0;i<10;i++)
        if(x[i] && x[i+1] && x[i+2] && x[i+3] && x[i+4])
            S=1;
    j=0;
    if(p)j=1;
    if(tp)j=2;
    if(t)j=3;
    if(S)j=4;
    if(f)j=5;
    if(t && p)j=6;
    if(k)j=7;
    if(f && S)
    {
        if(x[9] && x[0])j=9;
        else j=8;
    }
    if(j)s0[n++]=hand(h,j);
}
void go(int d,int i,int h=0)
{
    if(d>=5)
    {
        test(h);
        return;
    }
    if(i>=52)return;
    s[i&3]++;
    x[i>>2]++;
    go(d+1,i+1,h*52+i);
    s[i&3]--;
    x[i>>2]--;
    go(d,i+1,h);
}
char tr[999];
int sc[99];
long long num[32];
double di[]={1.0,47.0,1081.0,16215.0,178365.0,1533939.0};
void go(char hp[])
{
    int i,j,k,l;
    for(i=0;i<n;i++)
    {
        for(j=k=0,l=s0[i].h;j<5;j++)
        {
            k|=hp[l%52];
            l/=52;
        }
        num[k]+=sc[s0[i].c];
    }

}
inline int bnt(int x)
{
    int n=0;
    while(x>0)n+=x%2,x/=2;
    return n;
}
void printlf(double a)
{
    printf("%lf\n",a);
}
main()
{
    tr['h']=0,tr['c']=1,tr['d']=2,tr['s']=3;
    tr['A']=0,tr['2']=1,tr['3']=2,tr['4']=3;
    tr['5']=4,tr['6']=5,tr['7']=6,tr['8']=7;
    tr['9']=8,tr['T']=9,tr['J']=10,tr['Q']=11,tr['K']=12;
    go(0,0);
    int i,m,T;
    char hp[52],tmp[99];
    scanf("%d",&T);
    while(T--)
    {
        for(i=1;i<=9;i++)
            scanf("%d",sc+i);
        scanf("%d",&m);
        while(m--)
        {
            for(i=0;i<32;i++)num[i]=0;
            for(i=0;i<52;i++)hp[i]=0;
            for(i=0;i<5;i++)
            {
                scanf("%s",tmp);
                hp[tr[tmp[0]]*4+tr[tmp[1]]]=(1<<i);
            }
            go(hp);
            double max=0;
            for(i=0;i<32;i++)
                max>?=num[i]/di[5-bnt(i)];
            printlf(max);
        }
    }
}
