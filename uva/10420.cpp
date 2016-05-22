#include<cstdio>
struct trie
{
    int num;
    char ch;
    trie *next,*child;
    bool find(char *s)
    {
        if(ch==s[0] && !s[1])
            return num;
        if(ch<s[0] && next)
            return next->find(s);
        if(ch==s[0] && child)
            return child->find(s+1);
        return 0;
    }
    int ins(char *s)
    {
        if(ch==s[0] && !s[1])
            return num++;
        if(ch<s[0])
        {
            if(!next || next->ch>s[0])
            {
                trie *ptr=new trie;
                ptr->next=next,next=ptr;
                ptr->ch=s[0],ptr->num=0,ptr->child=NULL;
            }
            return next->ins(s);
        }
        if(ch==s[0])
        {
            if(!child)
            {
                child=new trie;
                child->next=child->child=0;
                child->ch=0,child->num=0;
            }
            return child->ins(s+1);
        }
        return 0;
    }
    void go(char *st,int n=0)
    {
        st[n]=ch;
        if(num)
        {
            st[n+1]=0;
            printf("%s %d\n",st,num);
        }
        if(child)child->go(st,n+1);
        if(next)next->go(st,n);
    }
}*s0;
main()
{
    int i,T;
    char s[100];
    s0=new trie;
    s0->num=s0->ch=0;
    s0->child=s0->next=NULL;
    scanf("%d%c",&T,s);
    while(T--)
    {
        gets(s);
        for(i=0;s[i] && s[i]!=' ';i++);
        s[i]=0,s0->ins(s);
    }
    s0->go(s);
    scanf(" ");
}
