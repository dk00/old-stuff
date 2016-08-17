#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long f[50];
long long calc(int num[],int n,int t)
{
    long long s1[25],s2[25];
    if(n<=1)return 1;
    for(j=0;j<=num[0] && j<=t;j++)
        s1[j]=f[t]/f[j];
    for(i=1;i<n;i++)
    {
        for(j=0;j<=t;j++)s2[j]=0;
        for(j=0;j<=num[i] && j<=t;j++)
            for(k=0;j+k<=t;k++)
                s2[j+k]+=s1[k]*(f[k]/f[j]);
        for(j=0;j<=t;j++)s1[j]=s2[j];
    }
    return s1[k];
}
int count(int s[],int n,int num[])
{
    for(i=j=0;i<n;i++,j++)
    {
        s[j]=s[i];
        for(num[j]=0;i<n && s[i]==s[j];i++)num[j]++;
    }
    return j;
}
int getseq(int s[])
{
    int n;
    char tmp[100];
    scanf("%[^{(]",tmp);
    scanf("%[{(]",tmp);
    for(n=0;tmp[0]!='}' && tmp[0]!=')';n++)
    {
        scanf("%[-0123456789]",tmp);
        sscanf(tmp,"%d",&s[n]);
        scanf("%[,})]",tmp);
    }
    s[n]=-1;
    return n+1;
}
void printset(int s[],int n)
{
    printf("(");
    if(n)printf("%d",s[0]);
    for(int i=1;i<n;i++)
        printf(",%d",s[i]);
    printf(")\n");
}
int s1[50];
main()
{
    int i,n1;
    for(i=f[0]=1;i<25;i++)f[i]=f[i-1]*i;
    char cmd[1000];
    while(scanf("%s",cmd) && stricmp(cmd,"end"))
    {
        if(!stricmp(cmd,"degrade"))
        {
            n1=getseq(s1);
            sort(s1,s1+n1);
            printset(s1,n1);
        }
    }
}
