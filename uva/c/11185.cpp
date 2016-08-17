#include<cstdio>
#include<cstdlib>
void print(int n)
{
    if(!n)return;
    print(n/3);
    putchar('0'+n%3);
}
main()
{
    int n;
    while(scanf("%d",&n) && n>=0)
        if(!n)puts("0");
        else print(n),puts("");
}
