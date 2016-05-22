#include<cmath>
#include<cstdio>
#include<algorithm>
const int N=300000;
struct pt
{
    double x,y;
    int operator-(pt a)const{return x+y-a.x-a.y;}
    bool operator<(pt a)const{return x+y<a.x+a.y;}
}s[N],st,ed;
int n;
char go(double r)
{
    for(i=j=0;j<n;)
        if(s[i]-s[j]<2*r)
        {
            ins(,);
        }
        else
        {
            del(,);
        }
}
main()
{
    while()
    {
        for(lb=0;ub-lb>1e-5;)
            if(go(r=(lb+ub)/2))lb=r+1e-7;
            else ub=r-1e-7;
    }
}
