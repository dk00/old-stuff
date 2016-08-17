#include<cstdio>
#include<cstring>
main()
{
    int i,j,k;
    char tmp[99];
    while(scanf("%s",tmp) && tmp[0]!='~')
    {
        k=0;
        while(tmp[0]!='#')
        {
            i=strlen(tmp);
            if(i<=2)j=2-i;
            else
                k=(k<<(i-2))|((j<<(i-2))-(j>0));
            scanf("%s",tmp);
        }
        printf("%d\n",k);
    }
}
