#include<cstdio>
int n,p;
char *tmp,s[2097153],*t[22];
int u[2097153];
void go(int v)
{
    int j=0;
    u[j++]=v;
    while(j)
    {
        v=u[j-1];
        if(s[v]>=0)
            u[j++]=v/2+n/2*s[v]--;
        else
            j--,tmp[p++]='0'+v%2;
    }
}
main()
{
    int i,j,T;
    t[0]=new char[3];
    t[0][0]='0',t[0][1]='1',t[0][2]=0;
    for(i=1,n=2;i<21;i++,n*=2)
    {
        p=0,t[i]=new char[n*2+i+2],tmp=t[i];
        for(j=0;j<n;j++)s[j]=1;
        for(j=0;j%2==0;j=j/2+n/2*s[j]--)
            if(j)tmp[p++]='0';
        go(j);
        for(j=0;j<i;j++)
            tmp[p++]='0';
        tmp[p]=0;
    }
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&j);
        for(i=p=0;i<n;i++)
            p=p*2+t[n-1][i+j]-'0';
        printf("%d\n",p);
    }
}
