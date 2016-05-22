#include<cstdio>
main()
{
    int i,j,n,s[40];
    while(scanf("%d",&n) && n)
    {
        for(i=j=0;n>0;j++,n/=2)
            i+=(s[j]=n%2);
        printf("The parity of ");
        while(j--)
            putchar(s[j]+'0');
        printf(" is %d (mod 2).\n",i);
    }
}
