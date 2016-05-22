#include<cstdio>
struct st
{
    char a;
    int x;
    st *ch,*ne;
}*root;
int n,max;
char tmp[1000000];
void clear(st *ptr)
{
    if(ptr)
    {
        clear(ptr->ne);
        clear(ptr->ch);
        delete ptr;
    }
}
char insert(char s[],st *&ptr=root)
{
    if(ptr==NULL)
    {
        ptr=new st;
        ptr->a=s[0],ptr->x=0;
        ptr->ch=ptr->ne=0;
    }
    if(s[0]!=ptr->a)
        return insert(s,ptr->ne);
    if(s[0])
        return insert(s+1,ptr->ch);
    ptr->x++;
    max>?=ptr->x;
}
char path[100];
char go(int d,st *ptr)
{
    if(ptr==NULL)return 0;
    if(ptr->x==max)
    {
        path[n]=0;
        puts(path);
        return 1;
    }
    for(;ptr!=NULL;ptr=ptr->ne)
    {
        path[d]=ptr->a;
        if(go(d+1,ptr->ch))return 1;
    }
    return 0;
}
main()
{
    int i;
    char c;
    while(scanf("%d %s",&n,tmp)==2)
    {
        for(i=max=0;tmp[i+n-1];i++)
        {
            c=tmp[i+n],tmp[i+n]=0;
            insert(tmp+i);
            tmp[i+n]=c;
        }
        go(0,root);
        clear(root),root=NULL;
    }
}
