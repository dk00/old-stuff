#include<cstdio>
main()
{
    int i,j,k,T;
    char s[2008];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",s);
        for(i=0;s[i];i++);
        for(j=i/2;j>=0;j--)
        {
            for(k=0;k<j;k++)
                if(s[i-j+k]!=s[i-j-j+k])
                    break;
            if(k>=j)break;
        }
        for(k=0;k<8;k++)
            putchar(s[i-j+k%j]);
        puts("...");
    }
}
