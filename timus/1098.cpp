#include<cstdio>
char s[30001];
main()
{
    int i,j,n;
    for(n=0;(s[n]=getchar())!=EOF;n++)
        if(s[n]=='\n')n--;
    for(i=1,j=0;i<=n;i++)
        j=(j+1999)%i;
    if(s[j]=='?')puts("Yes");
    else if(s[j]==' ')puts("No");
    else puts("No comments");
}
