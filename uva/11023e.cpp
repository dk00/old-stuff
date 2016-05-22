#include<cstdio>
#include<algorithm>
using namespace std;
long long f[25],rec[1048576];
int o[25];
void clear(){for(int i=0;i<1048576;i++)rec[i]=-1;}
long long *seek(int u[],int n)
{
    int i,j,k;
    for(i=k=0;i<n;i++)
    {
        for(j=0;j<u[i];j++)
            k=k*2+1;
        for(;j<o[i];j++)
            k*=2;
    }
    return rec+k;
}
long long calc(int u[],int n,int k)
{
    if(k==0)return 1;
    int i,j;
    long long *p,num=0,t[25]={-1};
    p=seek(u,n);
    if(*p>=0)return *p;
    for(i=0;i<n;i++)
        if(u[i])
        {
            u[i]--;
            if(t[u[i]]<0)
                t[u[i]]=calc(u,n,k-1);
            num+=t[u[i]];
            u[i]++;
        }
    return(*p=num);
}
int get(int s[])
{   int n;
    char *p,tmp[5000];
    scanf("%s",tmp);
    p=strtok(tmp+1,",");
    for(n=0;p;n++)
    {
        sscanf(p,"%d",&s[n]);
        p=strtok(NULL,",");
    }
    return n;
}
int get(int s1[],int u1[],int s2[],int n2)
{
    int i,n1;
    for(i=0;i<n2;i++)s1[i]=s2[i];
    sort(s1,s1+n2);
    for(n1=i=0;i<n2;o[n1]=u1[n1++])
    {
        s1[n1]=s1[i];
        for(u1[n1]=1,i++;i<n2 && s1[n1]==s1[i];i++,u1[n1]++);
    }
    return n1;
}
main()
{
    int i,j,s1[25],u1[25],s2[25],n1,n2,tmp[25];
    long long k,l;
    char cmd[2000];
    for(f[0]=i=1;i<21;i++)f[i]=f[i-1]*i;
    while(scanf("%s",cmd) && cmd[3])
    {
        clear();
        if(cmd[3]=='r')
        {
            n2=get(s2);
            sort(s2,s2+n2);
            printf("(");
            for(i=0;i<n2;i++)
                printf("%d",s2[i]),i<n2-1?putchar(','):0;
            puts(")");
        }
        else if(cmd[3]=='m' || cmd[3]=='i')
        {
            n2=get(s2);
            n1=get(s1,u1,s2,n2);
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
            printf("{");
            for(i=0;i<n2;i++)
                printf("%d",s2[i]),i<n2-1?putchar(','):0;
            puts("}");
        }
        else
        {
            n2=get(s2);
            if(cmd[3]=='d')
                n1=get(tmp),n1=get(s1,u1,tmp,n1);
            else n1=get(s1,u1,s2,n2);
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
