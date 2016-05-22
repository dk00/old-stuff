#include<cstdio>
#include<cstring>
const int N=1001;
int n,p[N],d[N],u[N],s[N],min[N],c1[N],c2[N];
char name[N][99],tmp[N][99];
int find(char s[])
{
    for(int i=0;i<n;i++)
        if(!strcmp(s,name[i]))return i;
}
int find(int v)
{
    if(v==p[v])return v;
    return p[v]=find(p[v]);
}
void uni(int a,int b)
{
    a=find(a),b=find(b);
    if(a==b)return;
    if(d[a]<d[b])p[a]=b;
    else p[b]=a;
    if(d[a]==d[b])d[a]++;
}
main()
{
    int i,sum;
    while(scanf("%d",&n)==1 && n)
    {
        for(i=0;i<n;i++)p[i]=i,d[i]=u[i]=0,min[i]=50000;
        for(i=0;i<n;i++)
            scanf("%s %d %s %d",name[i],c1+i,tmp[i],c2+i);
        for(i=0;i<n;i++)
        {
            uni(i,s[i]=find(tmp[i]));
            if(s[i]==i)c2[i]=c1[i];
            u[s[i]]=1;
        }
        for(i=sum=0;i<n;i++)
        {
            sum+=c2[i];
            if(u[i])
                min[find(i)]<?=c1[i]-c2[i];
        }
        for(i=0;i<n;i++)
            if(u[i] && p[i]==i)
                sum+=min[i];
        printf("%d\n",sum);
    }
}
