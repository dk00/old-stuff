#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=22;
int n,W,len[N],sum[N];
struct Stat
{
    int d,s[5];
    bool operator<(Stat a)const{
        if(d!=a.d)return d<a.d;
        for(int i=0;i<W;i++)
            if(s[i]!=a.s[i])
                return s[i]<a.s[i];
        return false;
    }
    Stat add(int i,int l){
        Stat tmp=*this;
        tmp.d++;
        tmp.s[i]+=l;
        sort(tmp.s,tmp.s+W);
        return tmp;        
    }
};
map<Stat,int> H;
int ub;
int go(int d,Stat s)
{
    if(H.count(s))return H[s];
    if(d>=n)return H[s]=s.s[0];
    int pre=-1,best=0,tmp=0;
    for(int i=0;i<W;i++)
        if(s.s[i]<ub)best++,tmp+=ub-s.s[i];
    if(d+best>n || tmp>=sum[n-1]-sum[d-1])
        return H[s]=-1;
    Stat t;
    for(int i=0;i<W;i++){
        t=s.add(i,len[d]);
        tmp=go(d+1,t);
        if(tmp>best)best=tmp;
    }
    if(best>ub)ub=best;
    return H[s]=best;
}
main()
{
    int i;
    while(scanf("%d %d",&W,&n)==2){
        for(i=0;i<n;i++)
            scanf("%d",len+i);
        sort(len,len+n);
        //reverse(len,len+n);
        sum[0]=len[0];
        for(i=1;i<n;i++)
            sum[i]=sum[i-1]+len[i];
        ub=0;
        printf("%d\n",go(0,(Stat){0,0,0,0,0,0}),0);
        printf("> %d\n",H.size());
        H.clear();
    }
}
