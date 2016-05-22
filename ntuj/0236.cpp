#include<set>
#include<list>
#include<string>
#include<cstdio>
using namespace std;
struct word
{
    string s;
    list<string> *to;
    bool operator<(word b)const{return s<b.s;}
    int len(){return s.length();}
}w0;
int w;
char last;
struct wordr
{
    string s;
    char spc;
    int len(){return s.length();}
    void print(int &now)
    {
        int tmp=len();
        if(now+tmp+(last==' ')>w || last=='\n')
            now=tmp,last='\n';
        else
            now+=tmp+(last==' ');
        if(last)putchar(last);
        printf("%s",s.c_str());
        last=spc;
    }
};
list<string> to[999];
char tmp[99999],tmp0[9999];
main()
{
    set<word> s;
    list<wordr> res,nil;
    int i,j,l,n,m,len;
    scanf("%d %d %d",&w,&l,&n);
    for(i=0;i<n;i++)
    {
        scanf("%s%c",tmp,tmp0);
        w0.s=tmp;
        w0.to=to+i;
        w0.to->clear();
        while(tmp0[0]!='\n')
        {
            scanf("%s%c",tmp,tmp0);
            w0.to->push_back(tmp);
        }
        s.insert(w0);
    }
    for(len=0;scanf("%s%c",tmp,tmp0)>0;)
    {
        res.push_back((wordr){tmp,tmp0[0]});
        len+=res.back().len();
        tmp0[0]=0;
    }
    list<wordr>::iterator ptr,next;
    list<string>::iterator p1;
    set<word>::iterator t;
    while(len<l)
        for(ptr=res.begin();ptr!=res.end();ptr=next)
        {
            next=ptr,next++;
            t=s.find((word){ptr->s,NULL});
            if(t==s.end())continue;
            list<string> &z=*(t->to);
            tmp[0]=ptr->spc;
            for(p1=z.begin();p1!=z.end();p1++)
            {
                p1++;
                if(p1==z.end())break;
                p1--;
                len+=p1->length();
                res.insert(ptr,(wordr){*p1,' '});
            }
            p1--;
            len-=ptr->len();
            ptr->s=*p1;
            len+=ptr->len();
        }
    for(j=last=0,ptr=res.begin();ptr!=res.end();ptr++)
        ptr->print(j);
    if(last=='\n')puts("");
}

