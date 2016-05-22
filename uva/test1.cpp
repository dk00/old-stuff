#include<cmath>
#include<cstdio>
main()
{
    int i;
    double tmp;
    for(i=0;i<50;i++)
    {
        tmp=log10(i)*i;
        printf("%-6lf\n",tmp);
        if(tmp>500000)break;
    }
    printf("%d\n",i);
    scanf(" ");
}
