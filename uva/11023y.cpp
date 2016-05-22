#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long f[50];
long long go(int num[],int n,int t)
{
    int i,j,k;
    long long s1[25],s2[25];
    if(n<=1)return 1;
    for(j=0;j<=t;j++)s1[j]=0;
    for(j=0;j<=num[0] && j<=t;j++)
        s1[j]=f[t]/f[j];
    for(i=1;i<n;i++)
    {
        for(j=0;j<=t;j++)s2[j]=0;
        for(j=0;j<=num[i] && j<=t;j++)
            for(k=0;j+k<=t;k++)
                s2[j+k]+=s1[k]/f[j];
        for(j=0;j<=t;j++)s1[j]=s2[j];
    }
    return s1[t];
}
int count(int s[],int n,int num[])
{
    int i,j;
    sort(s,s+n);
    for(i=j=0;i<n;j++)
    {
        s[j]=s[i];
        for(num[j]=0;i<n && s[i]==s[j];i++)num[j]++;
    }
    return j;
}
void make(int s1[],int u1[],const int& n1,int s2[],int n2,long long k)
{
    int i,j;
    long long l;
    for(i=0;i<n2;i++)
        for(j=0;j<n1;j++)
        {
            if(!u1[j])continue;
            s2[i]=s1[j],u1[j]--;
            l=go(u1,n1,n2-i-1);
            if(k<=l)break;
            k-=l,u1[j]++;
        }
}
long long get(int s1[],int u1[],int n1,int s2[],int n2)
{
    int i,j;
    long long k=0;
    for(i=0;i<n2;i++)
        for(j=0;j<n1;j++)
        {
            u1[j]--;
            if(s2[i]==s1[j])break;
            k+=go(u1,n1,n2-i-1);
            u1[j]++;
        }
    return k;
}
int getseq(int s[])
{
    int n;
    char tmp[100];
    scanf("%[^{(]",tmp);
    scanf("%[{(]",tmp);
    for(n=0;tmp[0]!='}' && tmp[0]!=')';)
    {
        scanf("%[-0123456789]",tmp);
        n+=sscanf(tmp,"%d",&s[n]);
        scanf("%[,})]",tmp);
    }
    s[n]=-1;
    return n;
}
void printseq(int s[],int n,char *q)
{
    putchar(q[0]);
    if(n)printf("%d",s[0]);
    for(int i=1;i<n;i++)
        printf(",%d",s[i]);
    puts(q+1);
}
int s1[50],s2[50],u1[50],u2[50];
main()
{
    int i,n1,n2;
    long long k;
    for(i=f[0]=1;i<25;i++)f[i]=f[i-1]*i;
    char cmd[1000];
    while(scanf("%s",cmd) && strcmp(cmd,"end"))
    {
        if(!strcmp(cmd,"degrade"))
        {
            n1=getseq(s1);
            sort(s1,s1+n1);
            printseq(s1,n1,"()");
        }
        if(!strcmp(cmd,"promote") || !strcmp(cmd,"derive"))
        {
            n1=n2=getseq(s1);
            n1=count(s1,n1,u1);
            if(!strcmp(cmd,"derive"))
                scanf("%d",&n2);
            scanf("%lld",&k);
            make(s1,u1,n1,s2,n2,k+1);
            printseq(s2,n2,"{}");
        }
        if(!strcmp(cmd,"rank") || !strcmp(cmd,"find"))
        {
            n1=getseq(s1);
            if(!strcmp(cmd,"rank"))
                for(i=0,n2=n1;i<n1;i++)s2[i]=s1[i];
            else n2=getseq(s2);
            n2=count(s2,n2,u2);
            k=get(s2,u2,n2,s1,n1);
            printf("%lld\n",k);
        }
    }
}
