#include<cstdio>
class test
{
    int x;
public:
    test(int st)
    {
        x=st;
        printf("start %d\n",x);
    }
};

test a;
main()
{
    test b;
}
