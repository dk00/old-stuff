#include<set>
#include<map>
#include<string>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int M=131071;
char tmp[9999],_x[9999],*x=_x+5;
int n,p[9999],z[128][120],cc[128];
struct ms
{
    int n,x[20];
    string k[20];
    void clear(){n=0;}
    int size(){return n;}
    void insert(char a[])
    {
        for(int i=0;i<n;i++)
            if(k[i]==a)
            {
                x[i]++;
                return;
            }
        k[n]=a;
        x[n++]=1;
    }
    int count(const string& a)
    {
        for(int i=0;i<n;i++)
            if(k[i]==a)return x[i];
        return 0;
    }
};
multiset<string> h[M+1];
void reset()
{
    for(int i=0;i<128;i++)
        cc[i]=0;
}
int go(int& l,int c){l^=z[c][cc[c]++];}
void ins(char a[])
{
    int i,l;
    reset();
    for(i=l=0;a[i];i++)
        go(l,a[i]);
    h[l%M].insert(a);
}
int go(char a[],int n,int l)
{
    int i=h[l%=M].size(),j;
    if(!i)return 0;
    string tmp;
    j=a[n],a[n]=0,tmp=a,a[n]=j;
    string::iterator x=tmp.begin(),y=tmp.end();
    if(tmp.length()>2)sort(++x,--y);
    return h[l].count(tmp);
}
void print(map<string,string> s,char x[],int i)
{
    if(!i)return;
    x[i]=0;
    if(i-p[i]>1)sort(x+p[i]+1,x+i-1);
    string tmp=s[x+p[i]];
    print(s,x,p[i]);
    printf("%s%c",tmp.c_str(),i==n?'\n':' ');
}
main()
{
    int i,j,k,l,m,T;
    for(i=0;i<128;i++)
        for(j=0;j<105;j++)
            z[i][j]=abs((rand()<<16)^rand());
    map<string,string> map;
    scanf("%d",&T);
    while(T--)
    {
        map.clear();
        for(i=0;i<M;i++)
            h[i].clear();
        scanf("%s %d",x,&i);
        while(i--)
        {
            scanf("%s",tmp);
            string t0=tmp;
            for(j=0;tmp[j];j++);
            if(j>1)sort(tmp+1,tmp+j-1);
            ins(tmp);
            map[tmp]=t0;
        }
        for(n=0;x[n];n++)p[n]=-1;
        p[n]=-1;
        p[0]=n+1;
        for(i=1;i<=n;i++)
        {
            reset();
            for(j=i-1,l=0,go(l,x[j]);p[i]!=-2 && j>=0;j--,go(l,x[j]))
                if(p[j]!=-1 &&(k=go(x+j,i-j,l)))
                {
                    if(p[i]>-1 || p[j]==-2 || k>1)p[i]=-2;
                    else p[i]=j;
                }
        }
        if(p[n]==-2)
            puts("ambiguous");
        else if(p[n]==-1)
            puts("impossible");
        else print(map,x,n);
    }
}
