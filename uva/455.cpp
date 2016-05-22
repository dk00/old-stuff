#include<cstdio>
char s[100];
char go(int k)
{
    int i,j;
    for(i=k;s[i];i+=k)
        for(j=0;j<k;j++)
            if(s[i+j]!=s[j])return 0;
    return 1;
}
main()
{
    int i,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",s);
        for(n=0;s[n];n++);
        for(i=1;i<n;i++)
            if(n%i==0 && go(i))break;
        printf("%d\n",i);
        if(T)puts("");
    }
}
