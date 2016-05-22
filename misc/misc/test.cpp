#include<cstdio>
main()
{
    int a,b;
    scanf("%d %d",&a,&b);
    __asm__ __volatile__(
        "addl %%ebx,%%eax"
        :"=a"(a)
        :"a"(a),"b"(b)
    );
    printf("%d\n",a);
}
