#include<cstdio>
#include<cstring>
char s[105][105],t[105][105];
main()
{
    int i,j,k=0,n;
    for(n=0;gets(s[n]);n++)
        k>?=strlen(s[n]);
    for(i=0;i<n;i++)
        for(j=0;j<102;j++)
            t[j][n-i-1]=s[i][j];
    for(i=0;i<k;i++)
    {
        for(j=102;j && !t[i][j];j--);
        for(;j>=0;j--)
            if(!t[i][j])t[i][j]=' ';
        puts(t[i]);
    }
}
