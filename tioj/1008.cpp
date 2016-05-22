#include<cstdio>
#include<algorithm>
#define arg /2
using namespace std;
const int Max=3309583;
struct cup
{
    char s[5];
}q[Max];
struct list
{
    int x;
    list *next;
}*h[Max];
int _u,n=5,t;
char ins(int x,list *&hh)
{
    list *ptr;
    for(ptr=hh;ptr;ptr=ptr->next)
        if(ptr->x==x)return 0;
    ptr=new list;
    ptr->x=x;
    ptr->next=hh;
    hh=ptr;
    return 1;
}
void clean(list *&ptr)
{
    if(ptr)
    {
        clean(ptr->next);
        delete ptr;
        ptr=0;
    }
}
int nnode=0;
char test(int s[],cup q[])
{
    if(nnode++>Max arg)throw -2;
    int i,code;
    for(i=0;i<n;i++)
        if(s[i]==t)throw 1;
    q[0]=(cup){{s[0],s[1],s[2],s[3],s[4]}};
    for(i=code=0;i<5;i++)
        code=code*50+s[i];
    return ins(code,h[code%Max]);
}
int ub[5];
char proc(char s0[],cup q[])
{
    int i,j,m=0,x[5],n=5;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(i!=j && s0[i] && s0[j]<ub[j])
            {
                copy(s0,s0+n,x);
                int tmp=x[i]+x[j];
                x[j]=tmp<?ub[j];
                x[i]=tmp-x[j];
                m+=test(x,q+m);
            }
    for(i=0;i<n;i++)
    {
        if(s0[i]==ub[i])continue;
        copy(s0,s0+n,x);
        x[i]=ub[i];
        m+=test(x,q+m);
    }
    for(i=0;i<n;i++)
    {
        if(s0[i]==0)continue;
        copy(s0,s0+n,x);
        x[i]=0;
        m+=test(x,q+m);
    }
    return m;
}
main()
{
    int i,j,k,l,step;
    list *ptr;
    while(scanf("%d",&j)==1 && n)
    {
        nnode=0;
        if(_u++)
            for(i=0;i<Max;i++)
                clean(h[i]);
        for(i=step=0;i<j;i++)
            scanf("%d",&ub[i]);
        scanf("%d",&t);
        for(;i<5;i++)ub[i]=0;
        try{q[0]=(cup){{0,0,0,0,0}};
        if(!t)throw 1;
        if(t>ub[0] && t>ub[1] && t>ub[2] && t>ub[3] && t>ub[4])
            ub[0]=ub[1]=ub[2]=ub[3]=ub[4]=ub[5]=0;
        for(i=k=0,j=1;i<j;i++)
        {
            j+=proc(q[i].s,q+j);
            if(i>=k)
                k=j-1,step++;
        }
        puts("-1");}
        catch(int find){
            if(find==-2)puts("-1");
            else printf("%d\n",step+1);
        }
    }
}
