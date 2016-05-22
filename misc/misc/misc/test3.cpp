#include<cstdio>
main()
{
    int i;
    for(i=0;i<100;i+=4)
    {
        printf("%2.1lf\n",i*6/(i*0.06+1));
    }
    scanf(" ");
}
