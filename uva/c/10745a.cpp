#include<cstdio>
#include<algorithm>
int num[256],l[16000],o[16000],t[16000],p[16000];
char s[16000][20],u[16000];
bool cmp1(int i,int j)
{
    return l[i]<l[j];
}
bool cmp2(int i,int j)
{
    int k;
    for(k=0;s[i][k] && s[j][k] && s[i][k]==s[j][k];k++);
    return s[i][k]<s[j][k];
}
bool cmp(char *a,char *b)
{
    int i,j=1;
    for(i=0;a[i];i++)num[a[i]]++;
    for(i=0;b[i];i++)
        if(--num[b[i]]<0)
        {
            j=0,i++;
            break;
        }
    while(i--)num[b[i]]++;
    for(i=0;a[i];i++)num[a[i]]--;
    return j;
}
int find(int v)
{
    if(v<0 || u[v])return v;
    p[v]=find(p[v]);
    return p[v];
}
main()
{
    int i,j,n;
    for(n=0;scanf("%s",s[n])==1;n++)
    {
        l[n]=strlen(s[n]);
        o[n]=n,u[n]=1,p[n]=n-1;
    }
    std::sort(o,o+n,cmp1);
    for(i=n-1;i>=0;i--)
    {
        if(!u[i])continue;
        for(j=p[i];j>=0;j=p[j])
        {
            if(!u[j] || cmp(s[o[i]],s[o[j]]))u[j]=0;
            p[j]=find(p[j]);
        }
    }
    for(i=j=0;i<n;i++)
        if(u[i])t[j++]=o[i];
    std::sort(t,t+j,cmp2);
    for(i=0;i<j;i++)
        puts(s[t[i]]);
    scanf(" ");
}
