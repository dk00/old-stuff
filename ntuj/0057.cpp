#include<cstdio>
char s1[999],s2[999];
int s[200][200];
main()
{
    int i,j,T;
    scanf("%d%c",&T,s1);
    while(T--)
    {
        gets(s1+1);
        gets(s2+1);
        for(i=1;s1[i];i++)
            for(j=1;s2[j];j++)
                if(s1[i]==s2[j])
                    s[i][j]=s[i-1][j-1]+1;
                else
                    s[i][j]=s[i-1][j]>?s[i][j-1];
        printf("%d\n",s[i-1][j-1]);
    }
}
