#include<cstdio>
#include<algorithm>
using namespace std;
char s0[1000001],s1[1000001];
int c[1000001];
int dec(char a[],char b[])
{
    int i,k,n=0;
    for(i=0;a[i];i++)
    {
        if('0'<=a[i] && a[i]<='9')
        {
            for(k=0;'0'<=a[i] && a[i]<='9';i++)
                k=k*10+a[i]-'0';
            for(i--,k--;k--;)
                b[n]=b[n++-1];
        }
        else b[n++]=i;
    }
    b[n]=0;
    return n;
}
main()
{
    int i,j,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",s0);
        for(n=0;s0[n];n++);
        copy(s0,s0+n,s1);
        n=dec(s1,s0);
        copy(s0,s0+n,s1);
        sort(s1,s1+n);
        for(i=j=0;i<n;i++)
        {
            if(i && s1[i]!=s1[i-1])j=0;
            for(;s0[j]!=s1[i];j++);
            c[i]=j++;
        }
        for(i=c[0];i;i=c[i])
            putchar(s0[i]);
        puts(".");
    }
}
