#include<ctype.h>
#include<stdio.h>
char map[
main()
{
    char c;
    int i,j,num[256];
    while(scanf("%c",&c)!=EOF)
    {
        for(i=0,j=1;i<256;i++)
            num[i]=-1;
        while(1)
        {
            if(isalpha(c))
            {
                if(num[c]==-1)
                num[c]=j++;
                printf("%d",num[c]);
            }
            else
                putchar(c);
            if(c=='%')
            {
                scanf("%c",&c);
                putchar(c);
                break;
            }
            if(scanf("%c",&c)==EOF)
                break;
        }
    }
    puts("%");
}

