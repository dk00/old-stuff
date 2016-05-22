#include<set>
#include<string>
#include<cstdio>
using namespace std;
struct node
{
    string name;
    int p;
    bool operator<(node x)const{return p<x.p;}
};
main()
{
    int n;
    char tmp[999];
    set<node> h;
    while(~scanf("%d",&n) && n)
    {
        node x;
        set<node>::iterator ptr;
        if(n==1)
        {
            scanf("%s %d",tmp,&x.p);
            x.name=tmp;
            h.insert(x);
        }
        else if(n==2)
        {
            if(!h.size())
            {
                puts("0");
                continue;
            }
            ptr=h.end();
            ptr--;
            printf("%s\n",ptr->name.c_str());
            h.erase(ptr);
        }
        else if(n==3)
        {
            if(!h.size())
            {
                puts("0");
                continue;
            }
            ptr=h.begin();
            printf("%s\n",ptr->name.c_str());
            h.erase(ptr);
        }
    }
}
