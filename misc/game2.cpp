#include<set>
#include<cstdio>
#include<cstdlib>
using namespace std;
struct pp
{
    int x;
    char y;
    bool operator<(pp a)const{return x<a.x;}
};
set<pp> s;
int count(int x)
{
    if(s.count((pp){x,0}))
        return s.find((pp){x,0})->y;
    if(!x)return 0;
    int i,sum=1;
    for(i=1<<30;(x&i)==0;i>>=1);
    for(;1-i%2;i|=i/2)
        if(!count(x^i))
        {
            s.insert((pp){x,1});
            return 1;
        }
    if(!count(x^i))
    {
        s.insert((pp){x,1});
        return 1;
    }
    s.insert((pp){x,0});
    return 0;
}
main()
{
    int i;
    char tmp[100];
    while(scanf("%d",&i))
        s.clear(),printf("%d %d\n",s.size(),count(i));
}
