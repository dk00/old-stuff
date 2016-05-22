#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct poly
{
    int n;
    long long s[25];
    void operator*=(poly a)
    {
        int i,j,n1=n,n2=a.n;
        long long s1[25],s2[25];
        for(i=0;i<=n1;i++)s1[i]=s[i];
        for(j=0;j<=n2;j++)s2[j]=a.s[j];
        for(i=0;i<=n1+n2;i++)s[i]=0;
        for(i=0;i<=n1;i++)
            for(j=0;j<=n2;j++)
                s[i+j]+=s1[i]*s2[j];
        n=n1+n2;
    }
};
bool u[25];
long long f[25];
long long go(int s[],int n,int k)
{
    poly a,b;
    a.n=0;
    a.s[0]=1;
    int i,j;
    for(i=0;i<n;i++)
        if(u[i] &&(!i || s[i]!=s[i-1]))
        {
            b.s[0]=1;
            for(j=0;s[i]==s[i+j];j++)
                b.s[j+1]=b.s[j]*(j+1);
            b.n=j;
            a*=b;
        }
    return f[k]/a.s[k];
}
void make(int s1[],int n1,int s2[],int n2,long long k)
{
    int i,j;
    long long l;
    for(j=0;j<n1;j++)u[j]=1;
    for(i=0;i<n2;i++)
        for(j=0;j<n1;j++)
        {
            if((j && s1[j]==s1[j-1])|| !u[j])continue;
            s2[i]=s1[j],u[j]=0;
            l=go(s1,n1,n2-i-1);
            if(k<=l)break;
            k-=l,u[j]=1;
        }
}
int getseq(int s[])
{
    int n;
    char tmp[1000];
    scanf("%[^{(]",tmp);
    scanf("%[{(]",tmp);
    for(n=0;tmp[0]!='}' && tmp[0]!=')';n++)
    {
        scanf("%[-0123456789]",tmp);
        sscanf(tmp,"%d",s+n);
        scanf("%[,})]",tmp);
    }
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
main()
{
    char cmd[100];
    int n1,n2,s1[25],s2[25];
    long long k;
    for(f[0]=k=1;k<25;k++)f[k]=f[k-1]*k;
    while(scanf("%s",cmd) && stricmp(cmd,"end"))
    {
        if(!stricmp(cmd,"degrade"))
        {
            n1=getseq(s1);
            sort(s1,s1+n1);
            printseq(s1,n1,"()");
        }
        if(!stricmp(cmd,"promote"))
        {
            n1=getseq(s1);
            scanf("%lld",&k);
            make(s1,n1,s2,n2=n1,k+1);
            printseq(s2,n2,"{}");
        }
        if(!stricmp(cmd,"derive"))
        {
            n1=getseq(s1);
            scanf("%d %lld",&n2,&k);
            make(s1,n1,s2,n2,k+1);
            printseq(s2,n2,"{}");
        }
    }
}
