/*
PROB:dinings
LANG:C++
*/
#include<string>
#include<cstdio>
#include<algorithm>
struct num
{
    string s;
    int u;
    bool operator<(num a)const
    {
        if(a.s!=s)return s<a.s;
        return u<a.u;
    }
};
char t0[30001][99];
num t1[30001];
int s[30001];
int find(num a,int i,int j)
{
    while(i<=j)
    {
        k=(i+j)/2;
        if(a<t1[k])j=k-1;
        else if(t1[k]<a)i=k+1;
        else return s[k];
    }
}
main()
{
    freopen("dinings.in","r",stdin);
    freopen("dinings.out","w",stdout);
    int i,j,n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%s",t0[i]);
        t1[i].s=t0[i];
        t1[i].u=i;
    }
    std::sort(t1,t1+n);
    for(s[0]=i=j=1;i<n;s[i++]=j)
        if(t1[i].s!=t1[i-1].s)j++;
    for(i=j=0;i<n;i++)
    {
        num tmp;
        tmp.s=t0[i],tmp.u=i;
        if(s[i]!=find(tmp,0,n-1))j++;
    }
    printf("%d\n",j);
}
