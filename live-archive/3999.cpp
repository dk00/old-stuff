const int N=1000002;
void rsort(int x[],int t0[],int t1[],int n,int m)
{
    static int num[N];
    int i;
    for(i=0;i<=m;i++)num[i]=0;
    for(i=0;i<n;i++)num[x[t0[i]]+1]++;
    for(i=1;i<=m;i++)num[i]+=num[i-1];
    for(i=0;i<n;i++)t1[num[x[t0[i]]]++]=t0[i];
}
void suffixarray(int text[],int t[],int m)
{
    int i,j,k,n;
    static int s[N*2],tmp[N+2];
    for(n=0;text[n];n++)s[n]=text[n],t[n]=n;
    for(i=n;i<n*2;i++)s[i]=0,t[i]=n;
    for(i=1;i<n;i*=2)
    {
        rsort(s+i,t,tmp,n,m);
        rsort(s,tmp,t,n,m);
        for(j=0;j<n;j++)tmp[j]=s[j];
        for(j=0,m=1;j<n;j++)
        {
            s[t[j]]=m;
            if(tmp[t[j]]!=tmp[t[j+1]] || tmp[t[j]+i]!=tmp[t[j+1]+i])m++;
        }
    }
}
int n,s[N],t[N],d[N],x[N],p[9],u[9];
char tmp[N+1];
void go(int s[],int t[],int d[],int n)
{
    int i,j,k;
    for(i=0;i<n;i++)x[t[i]]=i;
    for(i=j=0;i<n;i++)
    {
        if(x[i]==n-1)
        {j=d[x[i]]=0;continue;}
        k=t[x[i]+1];
        while(s[i+j]==s[k+j])
            j++;
        d[x[i]]=j;
        j-=(j>0);
    }
}
int get(int x)
{
    int i;
    for(i=0;i<n;i++)
        if((!i || x>p[i-1]) && x<=p[i])
            return i;
}
#include<map>
#include<cstdio>
void print(int x)
{
    printf("%d %d ",t[x],d[x]);
    int i=0;
    for(i=t[x];s[i];i++)
        putchar(s[i]);
    puts("");
}

using namespace std;
main()
{
    int i,j,k,l,T,a;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=l=0;i<n;i++)
        {
            scanf("%s",tmp);
            for(j=0;tmp[j];j++,l++)
                s[l]=tmp[j];
            s[l++]='T'+i+1;
            u[i]=0,p[i]=l;
        }
        s[l]=0;
        suffixarray(s,t,'T'+n+1);
        go(s,t,d,l);
        map<int,int> h;
        u[get(t[0])]=1;
        for(i=j=a=0,k=1;s[t[j]]<='T' && j<l;i++)
        {
            while(s[t[j]]<='T' && j+1<l && k<n)
            {
                h[d[j]]++;
                if(!u[get(t[++j])]++)k++;
            }
            if(k<n)break;
            a>?=(h.begin())->first;
            if(!--h[d[i]])h.erase(d[i]);
            if(!--u[get(t[i])])k--;
        }
        printf("%d\n",a);
    }
}
