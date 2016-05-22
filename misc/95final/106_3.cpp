#include<cstdio>
#include<algorithm>
struct eg
{
    int a,b;
    bool operator<(eg x)const{return(a<x.a ||(a==x.a && b<x.b));}
}tmp[60000];
int n,m,s[60000],dg[60000],q[60000],d[60000],t[60000],c[60000],u[60000];
void proce(int& j)
{
    int i;
    std::sort(tmp,tmp+m);
    for(i=0;i<m;i++)
    {
        s[tmp[i].a]++;
        c[i]=tmp[i].b-1;
        dg[c[i]]++;
    }
    for(i=j=0;i<n;i++)
    {
        s[i+1]+=s[i];
        if(dg[i]==0)q[j++]=i;
    }
}
main()
{
    int i,j,k,max;
    freopen("in_3.txt","r",stdin);
    scanf("%d %d",&n,&m);
    for(i=0;i<n;i++)
        scanf("%d",&t[i]);
    for(i=s[0]=0;i<m;i++)
        dg[i]=s[i+1]=0,scanf("%d %d",&tmp[i].a,&tmp[i].b);
    proce(j);
    for(i=0;i<j;i++)
        d[q[i]]=t[q[i]];
    for(i=max=0;i<j;i++)
        for(k=s[q[i]];k<s[q[i]+1];k++)
        {
            if(--dg[c[k]]<=0)q[j++]=c[k];
            d[c[k]]>?=(d[q[i]]+t[c[k]]);
            max>?=d[c[k]];
        }
    for(i=0;i<m;i++)
        j=tmp[i].a,tmp[i].a=tmp[i].b,tmp[i].b=j;
    for(i=0;i<n;i++)
        dg[i]=s[i+1]=0,u[i]=(d[i]==max);
    proce(j);
    for(i=0;i<j;i++)
        for(k=s[q[i]];k<s[q[i]+1];k++)
        {
            if(--dg[c[k]]<=0)q[j++]=c[k];
            if(u[q[i]] && d[c[k]]+t[q[i]]==d[q[i]])
                u[c[k]]=1;
        }
    for(i=j=0;i<n;i++)
        j+=u[i];
    printf("%d\n",j);
}
