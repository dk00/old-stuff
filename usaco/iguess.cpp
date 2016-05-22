/*
PROB:iguess
LANG:C++
*/
#include<cstdio>
main()
{
    setlinebuf(stdout);
    unsigned i,j,k;
    char tmp[99];
    scanf("%u",&j);
    i=1,k=(i+j)/2;
    printf("%u\n",k);
    while(scanf("%s",tmp)==1)
    {
        if(tmp[0]=='L')i=k+1;
        else if(tmp[0]=='H')j=k-1;
        else break;
        printf("%u\n",k=(i+j)/2);
    }
}
