#include<cstdio>
struct node
{
    node *c[52],*sub;
    int b;
}*root;
char s[100002],s0[1000][1002];
int tbl[256],next[1000],able[1000];
void clear(node **ptr)
{
    if(!*ptr)
        return;
    for(int i=0;i<52;i++)
        clear(&(*ptr)->c[i]);
    delete *ptr;
    *ptr=NULL;
}
void build(node *&ptr,char *a,int b)
{
    if(!ptr)
    {
        ptr=new node;
        for(int i=0;i<52;i++)
            ptr->c[i]=NULL;
        ptr->b=-1;
    }
    if(*a)
        build(ptr->c[tbl[*a]],a+1,b);
    else
    {
        int *i;for(i=&ptr->b;*i!=-1;i=&next[*i]);
        *i=b;
    }
}
void link(char *a)
{
    int i=1;
    node *ptr1,*ptr2;
    root->c[tbl[a[0]]]->sub=root;
    ptr1=root->c[tbl[a[0]]];
    ptr2=root;
    while(a[i])
    {
        ptr1=ptr1->c[tbl[a[i]]];
        while(ptr2!=root && !ptr2->c[tbl[a[i]]])
            ptr2=ptr2->sub;
        if(ptr2->c[tbl[a[i]]])
            ptr2=ptr2->c[tbl[a[i]]];
        i++;
        ptr1->sub=ptr2;
    }
}
main()
{
    node *ptr;
    int i,j,k,q,t;
    char tmp[100];
    for(i='a';i<='z';i++)
        tbl[i]=i-'a';
    for(i='A';i<='Z';i++)
        tbl[i]=i-'A'+26;
    scanf("%d%c",&t,tmp);
    while(t--)
    {
        gets(s);
        clear(&root);
        scanf("%d%c",&q,tmp);
        for(i=0;i<q;i++)
        {
            able[i]=0,next[i]=-1;
            gets(s0[i]);
            build(root,s0[i],i);
            link(s0[i]);
        }
        for(i=0,ptr=root;s[i];i++)
        {
            while(!ptr->c[tbl[s[i]]] && ptr!=root)
                ptr=ptr->sub;
            if(ptr->c[tbl[s[i]]])
                ptr=ptr->c[tbl[s[i]]];
            for(j=ptr->b;j!=-1;j=next[j])
                able[j]=1;
        }
        for(i=0;i<q;i++)
            if(able[i])
                puts("y");
            else puts("n");
    }
}
