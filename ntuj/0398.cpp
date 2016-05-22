#include<cstdio>
main()
{
    int i,x;
    char c[999];
    while(~scanf("%s",c) && c[0]!='0')
    {
        printf("%s: ",c);
        for(x=i=0;c[i];i++)
            x=x*9+c[i]-'0'-(c[i]>'4');
        printf("%d\n",x);
    }
}
