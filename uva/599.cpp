#include<cstdio>
main()
{
    char a,b,s[256],tmp[100];
    short i,k;
    int T;
    scanf("%d\n",&T);
    while(T--)
    {
        for(char j='A';j<='Z';j++)s[j]=0;
        a=b=0;
        while(gets(tmp) && tmp[0]!='*')
        {
            b--;
            if(!s[tmp[1]]++)a--;
            if(!s[tmp[3]]++)a--;
        }
        gets(tmp);
        for(i=0;tmp[i];i++);
        i++;
        a+=i>>=1,b+=i;
        printf("There are %d tree(s) and %d acorn(s).\n",b-a,a);
    }
}
