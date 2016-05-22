#include<cstdio>
int n;
long long s1[100][100],s2[100][100];
char op[1000],u1[100][100],u2[100][100];
long long min(int,int);
long long go(int,int);
long long min(int st,int ed)
{
    if(u2[st][ed])return s2[st][ed];
    u2[st][ed]=1;
    int i;
    for(i=st;i+1<=ed;i++)
    {
        if(op[i]=='+')
            s2[st][ed]<?=(min(st,i)+min(i+1,ed));
        if(op[i]=='-')
            s2[st][ed]<?=(min(st,i)-go(i+1,ed));
        if(op[i]=='*')
        {
            s2[st][ed]<?=(go(st,i)*go(i+1,ed));
            s2[st][ed]<?=(go(st,i)*min(i+1,ed));
            s2[st][ed]<?=(min(st,i)*go(i+1,ed));
            s2[st][ed]<?=(min(st,i)*min(i+1,ed));
        }
    }
    return s2[st][ed];
}
long long go(int st,int ed)
{
    if(u1[st][ed])return s1[st][ed];
    u1[st][ed]=1;
    int i;
    for(i=st;i+1<=ed;i++)
    {
        if(op[i]=='+')
            s1[st][ed]>?=(go(st,i)+go(i+1,ed));
        if(op[i]=='-')
            s1[st][ed]>?=(go(st,i)-min(i+1,ed));
        if(op[i]=='*')
        {
            s1[st][ed]>?=(go(st,i)*go(i+1,ed));
            s1[st][ed]>?=(min(st,i)*min(i+1,ed));
            s1[st][ed]>?=(go(st,i)*min(i+1,ed));
            s1[st][ed]>?=(min(st,i)*go(i+1,ed));
        }
    }
    return s1[st][ed];
}
main()
{
    int i,j;
    char tmp[1000];
    while(1)
    {
        for(n=0;;n++)
        {
            if(scanf("%[0123456789]",tmp)<0)return 0;
            u1[n][n]=u2[n][n]=1,sscanf(tmp,"%d",&s1[n][n]);
            s2[n][n]=s1[n][n];
            if(scanf("%c",op+n)!=1 || op[n]=='\n')break;
        }
        for(i=0;i<=n;i++)
            for(j=i+1;j<=n;j++)
                s1[i][j]=-2147483647,s2[i][j]=2147483647,u1[i][j]=u2[i][j]=0;
        printf("%lld\n",go(0,n));
    }
}
