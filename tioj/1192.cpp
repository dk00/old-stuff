#include<cstdio>
#include<cstring>
#include<algorithm>
int n,s1[1000][1000],s2[1000][1000];
char c[1000][1000],u[1000];
inline char test(int a[],int b[])
{
    int i=0,j=0;
    while(a[i] && b[j])
        if(a[i]==b[j])return 1;
        else if(a[i]<b[j])i++;
        else j++;
    return 0;
}
inline char go(int v,char x)
{
    if(u[v]>=0)return u[v]==x;
    u[v]=x;
    for(int i=0;i<n;i++)
        if(c[v][i] && !go(i,!x))return 0;
    return 1;
}
main()
{
    int i,j,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&i);
        for(i=0;i<n;i++)
        {
            for(j=0;scanf("%d",&s1[i][j]) && s1[i][j];j++);
            std::sort(s1[i],s1[i]+j);
            for(j=0;scanf("%d",&s2[i][j]) && s2[i][j];j++);
            std::sort(s2[i],s2[i]+j);
        }
        memset(u,-1,n);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=(test(s1[i],s2[j]) || test(s2[i],s1[j]));
        for(i=0;i<n;i++)
            if(u[i]==-1 && !go(i,0))break;
        puts((i>=n)?"Yes":"No");
    }
}
