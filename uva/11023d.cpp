#include<cstdio>
#include<algorithm>
using namespace std;
long long f[25];
int getseq(int s[])
{
    int n;
    char *p,tmp[1000];
    scanf("%s",tmp);
    p=strtok(tmp+1,",");
    for(n=0;p && sscanf(p,"%d",&s[n])==1;n++)
        p=strtok(NULL,",");
    return n;
}
int makeset(int s[],int u[],int s2[],int n2)
{
    int i,n,s0[25];
    if(!n2)return 0;
    copy(s2,s2+n2,s0);
    sort(s0,s0+n2);
    s[0]=s0[0],u[0]=1;
    for(i=n=1;i<n2;i++)
        if(s0[i]!=s0[i-1])
            s[n]=s0[i],u[n++]=1;
        else u[n-1]++;
    return n;
}
int getset(int s[],int u[])
{
    int n0,s0[1000];
    n0=getseq(s0);
    return makeset(s,u,s0,n0);
}
long long calc(int u[],int n,int k)
{
    int i,j,l;
    long long t[25]={0};
    t[0]=f[k];
    for(l=0;l<n;l++)
    for(i=k;i>0;i--)
        for(j=1;i-j>=0 && j<=u[l];j++)
            t[i]+=t[i-j]/f[j];
    return t[k];
}
main()
{   char cmd[1000];
    long long k,l;
    int i,j,n1,n2,s1[25],s2[25],u1[25];
    for(k=f[0]=1;k<21;k++)
        f[k]=f[k-1]*k;
    while(scanf("%s",cmd) && cmd[3])
    {
        if(cmd[3]=='r')
        {
            n1=getseq(s1),sort(s1,s1+n1);
            putchar('(');
            for(i=0;i<n1;i++)
                printf("%d",s1[i]),i<n1-1?putchar(','):0;
            puts(")");
        }
        else if(cmd[3]=='m' || cmd[3]=='i')
        {
            n1=getset(s1,u1);
            if(cmd[3]=='m')n2=n1;
            else scanf("%d",&n2);
            scanf("%lld",&k);
            for(i=0;i<n2;u1[j]--,s2[i++]=s1[j])
                for(j=0;j<n1;j++)
                {
                    if(!u1[j])continue;
                    u1[j]--;
                    l=calc(u1,n1,n2-i-1);
                    u1[j]++;
                    if(k>=l)k-=l;
                    else break;
                }
            for(putchar('{'),i=0;i<n2;i++)
                printf("%d",s2[i]),i<n2-1?putchar(','):0;
            puts("}");
        }
        else
        {
            n2=getseq(s2);
            if(cmd[3]=='k')n1=makeset(s1,u1,s2,n2);
            else n1=getset(s1,u1);
            for(i=k=0;i<n2;i++,u1[j]--)
                for(j=0;s1[j]<s2[i];j++)
                {
                    if(!u1[j])continue;
                    u1[j]--;
                    k+=calc(u1,n1,n2-i-1);
                    u1[j]++;
                }
            printf("%lld\n",k);
        }
    }
}
