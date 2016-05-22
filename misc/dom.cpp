#include<set>
#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100000,Max=131071;
struct pt{int v,l;bool operator<(pt a)const{return v<a.v;}};
struct ma{
    set<pt> s[N*2+1];
    int update(unsigned x,unsigned y)
    {
        unsigned i,l=1,r=1;
        for(i=0;x<=Max;x+=x&(1<<i++)){
            set<pt>::iterator p=s[i].lower_bound(y),q=p;
            l=s[i].size();
            if(q!=s[i].begin())l=(--q)->l+1;
            if(p!=s[i].end())s[i].erase(p);
            s[i].insert((pt){y,l});
            r>?=l;
        }
        return r;
    }
}S;
int fix(int w[],int h[],int n)
{
    static int i,x,tmp[2*N];
    map<int,int> V;
    copy(w,w+n,tmp);
    copy(h,h+n,tmp+n);
    sort(tmp,tmp+2*n);
    for(i=0;i<2*n;i++)
        if(!V.count(tmp[i]))
            x=V[tmp[i]]=V.size();
    for(i=0;i<n;i++)
        w[i]=V[w[i]],h[i]=V[h[i]];
    return V.size();
}
int n,w[N],h[N],s0[N],s1[N];
void go(int len[])
{
    int i,ub=0;
    S.clear();
    for(i=0;i<n;i++)S.s[i].clear();
    for(i=0;i<n;i++)
        len[i]=1+(S.update(w[i],h[i])>?S.update(h[i],w[i]));
}
main()
{
    int i,j,lmax;
    while(scanf("%d",&n)==1){
        for(i=0;i<n;i++)
            scanf("%d %d",w+i,h+i);
        lmax=fix(w,h,n);
        reverse(w,w+n),reverse(h,h+n);
        go(s0);
        for(i=0;i<n;i++)
            w[i]=lmax-w[i]+1,h[i]=lmax-h[i]+1;
        go(s1);
        for(i=j=0;i<n;i++)
            j>?=s0[i]+s1[i];
        printf("%d\n",j-1);
    }
}
