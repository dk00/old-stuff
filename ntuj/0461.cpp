#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
struct bu{
    int p,h;
    bool operator<(bu b)const{
        if(p!=b.p)return p<b.p;
        return h>b.h;
    }
}s[90000];
main()
{
    int i,j,n;
    long long sum;
    while(scanf("%d",&n)>0)
    {
        for(i=sum=0;i<n;i++)
        {
            scanf("%d %d %d",&s[i].p,&s[n+i].p,&s[i].h);
            s[n+i].h=-s[i].h;
        }
        sort(s,s+n*2);
        map<int,int> h;
        for(i=0;i<n*2;i++)
        {
            if(h.size())
            {
                map<int,int>::iterator p=h.end();
                j=(--p)->first;
                sum+=j*1ll*(s[i].p-s[i-1].p);
            }
            if(s[i].h>0)h[s[i].h]++;
            else h[s[i].h*=-1]--;
            if(!h[s[i].h])
                h.erase(s[i].h);
        }
        printf("%I64d\n",sum);
    }
}
