#include<set>
#include<string>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
struct stu
{
    string s;
    int p;
    bool operator<(stu x)const{return s<x.s;}
};
struct proj
{
    string s;
    int num;
    bool operator<(proj x)const
    {return(num>x.num ||(num==x.num && s<x.s));}
}p[100];
char u[10000];
main()
{
    set<stu> s;
    string t;
    char tmp[1000];
    int i,n;
    while(1)
    {
        s.clear();
        for(n=0;scanf("%[^\n]",tmp);)
        {
            t=tmp;
            if(tmp[0]=='0' || tmp[0]=='1')break;
            if('A'<=tmp[0] && tmp[0]<='Z')
                p[n++]=(proj){t,0};
            else
            {
                set<stu>::iterator ptr=s.find((stu){t,0});
                if(ptr!=s.end())
                {
                    if(ptr->p>=0 && ptr->p!=n-1)
                    {
                        p[ptr->p].num--;
                        s.erase(ptr);
                        s.insert((stu){t,-1});
                    }
                }
                else s.insert((stu){t,n-1}),p[n-1].num++;
            }
            scanf("%c",tmp);
        }
        scanf("%c",tmp);
        if(t=="0")break;
        sort(p,p+n);
        for(i=0;i<n;i++)
            printf("%s %d\n",p[i].s.c_str(),p[i].num);
    }
}
