#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100001;
struct node
{
    int d,v[4],to[4];
    void add(int x){to[d++]=x;}
}tmp[10001],s[10001];
struct nums
{
    int u,v[4];
    void operator=(node x)
    {
        int i,j;
        for(i=0;i<4;i++)
            v[i]=x.v[i];
        for(i=0;i<4;i++)
            for(j=1;j<4;j++)
                if(v[j]<v[j-1])
                    swap(v[j],v[j-1]);
    }
    bool operator<(nums x)const
    {
        for(int i=0;i<4;i++)
            if(v[i]!=x.v[i])return v[i]<x.v[i];
        return 0;
    }
}tmp0[N];
int num[N];
void go(int k)
{
    int i;
    node& x=tmp[k];
    for(i=0;i<x.d;i++)
        if(num[x.to[i]]<0)
            s[x.to[i]].add(k);
}
char test(int s[],int n,int k)
{
    int i,j;
    for(i=0;i<n;i+=k)
        for(j=0;j<k;j++)
            if(s[j]!=s[i+j])return 1;
    return 0;
}
bool notp[100000];
int pn,pr[9999];
int calc(int s[],int n)
{
    pr[0]=2,pn=1;
    int i,j;
    for(i=3;i<n;i++,i++)
    {
        if(notp[i])continue;
        pr[pn++]=i;
        if(11l*i*i>=n)continue;
        for(j=i*i;j<n;j+=i*2)
            notp[j]=1;
    }
    for(i=0;i<pn;i++)
        while(n%pr[i]==0)
        {
            if(test(s,n,n/pr[i]))break;
            n/=pr[i];
        }
    return n;
}
int count(int v)
{
    int i,j,sum=1;
    for(i=0;i<s[v].d;i++)
    {
        for(j=0;j<i;j++)
            if(num[s[v].to[i]]==num[s[v].to[j]])
                break;
        if(j>=i)
            sum+=count(s[v].to[i]);
    }
    return sum;
}
int cn,cy[N],dg[N],q[N];
main()
{
    int i,j,k,l,n,m;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        num[i]=-1;
        scanf("%d %d",&j,&k);
        j--,k--;
        tmp[j].add(k);
        tmp[k].add(j);
    }
    for(i=j=0;i<n;i++)
        if((dg[i]=tmp[i].d)==1)
            num[q[j++]=i]=0;
    for(l=j,i=m=0;i<j;i++)
    {
        go(q[i]);
        dg[q[i]]--;
        for(k=0;k<tmp[q[i]].d;k++)
            if(dg[tmp[q[i]].to[k]]>0)
            {
                if(!--dg[tmp[q[i]].to[k]])
                    q[j++]=tmp[q[i]].to[k];
                swap(tmp[q[i]].to[k],tmp[q[i]].to[--tmp[q[i]].d]);
            }
        for(k=0;k<tmp[q[i]].d;k++)
            tmp[q[i]].v[i]=num[tmp[q[i]].to[i]];
        tmp0[m]=tmp[q[i]];
        tmp0[m++].u=q[i];
        if(i+1==l)
        {
            sort(tmp0,tmp0+m);
            for(l=k=0;l<m;l++)
            {
                if(l &&(tmp0[l]<tmp0[l-1] || tmp0[l-1]<tmp0[l]))k++;
                num[tmp0[l].u]=i+k;
            }
            l=j,m=0;
        }
    }
    for(i=0;num[i]>=0;i++);
    tmp0[m=0]=tmp[i];
    tmp0[m++].u=i;
    num[i]=-2;
    cn=1,cy[0]=i;
    while(1)
    {
        for(k=0;k<tmp[i].d && num[tmp[i].to[k]]!=-1;k++);
        if(k>=tmp[i].d)break;
        cy[cn++]=tmp[i].to[k];
        num[i]=-2;
        for(k=l;k<tmp[i].d;k++)
            if(!dg[tmp[i].to[k]])
            {
                swap(tmp[i].to[l++],tmp[i].to[k]);
                break;
            }
        tmp[i].d=l;
        i=cy[cn-1];
        tmp0[m]=tmp[i];
        tmp0[m++].u=i;
    }
    sort(tmp0,tmp0+m);
    for(l=k=0;l<m;l++)
    {
        if(l &&(tmp0[l]<tmp0[l-1] || tmp0[l-1]<tmp0[l]))k++;
        num[tmp0[l].u]=j+k;
    }
    l=calc(cy,cn);
    for(i=j=0;i<l;i++)
        j+=count(cy[i]);
    printf("%d\n",j);
}
