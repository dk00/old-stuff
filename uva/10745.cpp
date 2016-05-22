#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
int num[27],u[16000];
bool cmp(const char *a,const char *b)
{
    int i,j;
    for(i=0;i<26;i++)num[i]=0;
    for(i=0;a[i];i++)num[a[i]-'a']++;
    for(i=0;b[i];i++)num[b[i]-'a']--;
    for(i=0;i<26;i++)
    {
        if(num[i]<0)return 0;
        j+=num[i];
    }
    return j;
}
int go(string *s,int n)
{
    if(n<2)return n;
    int i,j,n1,n2;
    n1=go(s,n/2);
    n2=go(s+n/2,n-n/2);
    for(i=0;i<n2;i++)
        s[n1+i]=s[n/2+i];
    for(i=0,n=n1+n2;i<n;i++)u[i]=1;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(i!=j && cmp(s[i].c_str(),s[j].c_str()))u[j]=0;
    string tmp;
    for(i=j=0;i<n;i++)
        if(u[i])
            tmp=s[i],s[i]=s[j],s[j++]=tmp;
    return j;
}
main()
{
    int n;
    char tmp[20];
    string *s;
    s=new string[16000];
    for(n=0;scanf("%s",tmp)==1;n++)
        s[n]=tmp;
    n=go(s,n);
    sort(s,s+n);
    for(int i=0;i<n;i++)
        puts(s[i].c_str());
    scanf(" ");
}
