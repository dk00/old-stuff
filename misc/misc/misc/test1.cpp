#include<cstdio>
class bigint
{
public:
    char *tostr()
    {
        puts("int");
    }
    bigint operator+(bigint a){}
};

class bighex:public bigint
{
public:
    bighex(bigint)
    char *tostr()
    {
        puts("hex");
    }
};
main()
{
    puts("a");
    bighex a,b;
    a=a+b;
    a.tostr();
    scanf(" ");
}

