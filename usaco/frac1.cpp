#include<cstdio>
struct pt
{
    int a,b;
    pt operator+(pt x){return(pt){a+x.a,b+x.b};}
};
int n;
void go(pt a,pt b)
{
    pt c=a+b;
    if(c.b>n)return;
    go(a,c);
    printf("%d/%d\n",c.a,c.b);
    go(c,b);
}
main()
{
    freopen("frac1.in","r",stdin);
    freopen("frac1.out","w",stdout);
    scanf("%d",&n);
    pt a=(pt){0,1},b=(pt){1,1};
    puts("0/1");
    go(a,b);
    puts("1/1");
}
/*
PROB:frac1
LANG:C++
*/
