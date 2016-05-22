#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long f[21];
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
int k,n1,n2,s1[25],u1[25],path[25];
void go(int d)
{
    if(k<0 || !d)
    {
        if(!k--)
        {
            printf("{%d",path[n2-1]);
            for(d=n2-1;d--;)
                printf(",%d",path[d]);
            puts("}");
        }
        return;
    }
    for(int i=0;i<n1;i++)
        if(u1[i])
        {
            u1[i]--;
            path[d-1]=s1[i];
            go(d-1);
            u1[i]++;
        }
}
main()
{
    char cmd[1000];
    while(scanf("%s",cmd) && strcmp(cmd,"end"))
    {
        n1=getset(s1,u1);
        scanf("%d",&n2);
        scanf("%d",&k);
        go(n2);
    }
}
