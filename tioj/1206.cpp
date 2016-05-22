#include<cstdio>
inline int test(char s[],int n,int l)
{
    for(int i=1;i<=l;i++)
        if(s[n-i]!=s[n-l-i])return 0;
    return 1;
}
char s[210000];
int t[210000];
main()
{
    int i,n,max;
    while(gets(s+1))
    {
        for(n=1;s[n];n++)t[n]=s[n]+t[n-1];
        for(max=0,i=(n-1)/2;i>0;i--)
            if(t[n-1]-2*t[n-1-i]+t[n-1-2*i]==0 && test(s,n,i))
                break;
        printf("%d\n",i);
    }
}
