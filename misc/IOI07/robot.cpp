#include<set>
#include<iostream>
using namespace std;
struct pt
{
    int x,y;
    bool operator<(pt a)const{return(x<a.x ||(x==a.x && y<a.y));}
    void operator+=(pt a){x+=a.x,y+=a.y;};
    void operator-=(pt a){x-=a.x,y-=a.y;};
}p;
const pt di[]={{1,0},{0,1},{0,-1},{-1,0}};
char cmdi[][7]={"down\n","right\n","left\n","up\n"};
char test(char d)
{
    char tmp[1000];
    cout<<cmdi[d];
    cin>>tmp;
    return(tmp[0]=='o');
}
set<pt> *ps,*pr;
char path[1001];
int go(int d,set<pt> &s=*ps,set<pt> &r=*pr)
{
    int i,sum=1;
    if(s.count(p))return 0;
    s.insert(p);
    for(i=0;i<4;i++)
    {
        p+=di[i];
        if(r.count(p) || s.count(p))goto skip;
        if(test(i))
        {
            sum+=go(i);
            test(3-i);
        }
        else r.insert(p);
    skip:p-=di[i];
    }
    return sum;
}
main()
{
    set<pt> s0,r0;
    s0.clear();
    ps=&s0;
    r0.clear();
    pr=&r0;
    printf("%d\n",go(0));
}
