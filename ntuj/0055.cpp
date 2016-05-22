#include<cstdio>
char s[999][7];
char test(char a[],char b[],char c[])
{
    for(int i=0;i<4;i++)
        if(a[i]==b[i] && b[i]==c[i]);
        else if(a[i]!=b[i] && b[i]!=c[i] && c[i]!=a[i]);
        else return 0;
    return 1;
}
main()
{
    int i,j,k,n,C=0;
    while(gets(s[0]))
    {
        if(C)puts("");
        C=0;
        printf("CARDS: %s",s[0]);
        if(s[0][0])
        for(n=1;gets(s[n]) && s[n][0];n++)
            printf(" %s",s[n]);
        puts("");
        printf("SETS: ");
        for(i=0;i<n;i++)
            for(j=i+1;j<n;j++)
                for(k=j+1;k<n;k++)
                    if(test(s[i],s[j],s[k]))
                        printf("%d. %s %s %s\n",++C,s[i],s[j],s[k]);
        if(!C)puts("*** None Found ***");
    }
}
