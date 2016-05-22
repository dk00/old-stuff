#include<vector>
#include<cstdio>
const int inf=2147483647;
struct edge{int t,c;};
using namespace std;
int a[5001],d[5001],q1[5001],q2[5001];
int sp(vector<edge> s[],int n,int st,int ed,int x=(1<<12))
{
    int i,j,k,l,v;
    vector<edge>::iterator p;
    for(i=0;i<n;i++)d[i]=0;
    while(x/=2)
    {
        for(i=0;i<n;i++)a[i]=inf;
        a[st]=0;
        q1[0]=st;
        for(i=k=l=0,j=1;i<j || k<l;)
        {
            if(i<j)v=q1[i++];
            else v=q2[k++];
            for(p=s[v].begin();p!=s[v].end();p++)
                if(a[v]+!!(x&p->c)<a[p->t])
                {
                    a[p->t]=a[v]+!!(x&p->c);
                    if(x&p->c)q2[l++]=p->t;
                    else q1[j++]=p->t;
                }
        }
        for(i=0;i<n;i++)
            if(d[i]<inf)
                d[i]=d[i]*2+a[i];
    }
    return d[ed]<inf?d[ed]:-1;
}
main()
{
    int i,j,k,n,m;
    vector<edge> s[5001];
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<n;i++)
            s[i].clear();
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            i--,j--;
            s[i].push_back((edge){j,k});
        }
        scanf("%d %d",&i,&j);
        printf("%d\n",sp(s,n,i-1,j-1));
    }
}
