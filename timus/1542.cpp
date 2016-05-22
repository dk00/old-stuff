#include<cstdio>
#include<cstring>
#include<algorithm>
struct node
{
    int t;
    char c;
    node *ne,*ch;
}*root;
struct word
{
    int t;
    char s[20];
    bool operator<(word a)const
    {
        if(t==a.t)return strcmp(s,a.s)<0;
        return t<a.t;
    }
}s[100001];
char ins(char a[],int t,node *&ptr=root)
{
    if(ptr && ptr->c!=a[0])
        return ins(a,t,ptr->ne);
    if(ptr==NULL)
    {
        ptr=new node;
        ptr->ne=ptr->ch=NULL;
        ptr->t=-1;
        ptr->c=a[0];
    }
    if(a[1])
        return ins(a+1,t,ptr->ch);
    ptr->t=t;
}
int m;
char p[20];
char go(int d,node *ptr)
{
    if(!ptr)return 0;
    if(ptr->t>=0)
    {
        p[d]=ptr->c;
        p[d+1]=0;
        s[m].t=-ptr->t;
        strcpy(s[m++].s,p);
    }
    go(d,ptr->ne);
    p[d]=ptr->c;
    go(d+1,ptr->ch);
}
char go(char a[],int d=0,node *ptr=root)
{
    if(!a[0])
    {
        go(d,ptr);
        std::sort(s,s+m);
        for(d=0;d<10 && d<m;d++)
            puts(s[d].s);
    }
    while(ptr && ptr->c!=a[0])ptr=ptr->ne;
    if(ptr)
    {
        p[d]=a[0];
        if(!a[1] && ptr->t>=0)
            s[m].t=-ptr->t,
            std::copy(p,p+d+1,s[m++].s);
        go(a+1,d+1,ptr->ch);
    }
}
main()
{
    int i,n;
    char tmp[100];
    scanf("%d",&n);
    while(n--)
    {
        scanf("%s %d",tmp,&i);
        ins(tmp,i);
    }
    scanf("%d",&n);
    while(n--)
    {
        scanf("%s",tmp);
        m=0,go(tmp);
        if(n)puts("");
    }
}
