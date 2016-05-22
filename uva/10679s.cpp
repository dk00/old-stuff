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
void link(char p[][1002],int m)
{
    int i,j;
    node *ptr1[1000],*ptr2[1000];
    for(i=0;i<m;i++)
    {
        ptr1[i]=root->c[tbl[p[i][0]]];
        ptr2[i]=root;
        ptr1[i]->sub=ptr2[i];
    }
    for(j=1;p[0][j];j++)
        for(i=0;p[0][j] && i<m;i++)
        {
            ptr1[i]=ptr1[i]->c[tbl[p[i][j]]];
            while(ptr2[i]!=root && !ptr2[i]->c[tbl[p[i][j]]])
                ptr2[i]=ptr2[i]->sub;
            if(ptr2[i]->c[tbl[p[i][j]]])
                ptr2[i]=ptr2[i]->c[tbl[p[i][j]]];
            ptr1[i]->sub=ptr2[i];
            if(ptr2[i]->b>0)
                ptr1[i]->b=ptr2[i]->b;
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
    for(i=0;tmp[i];i++);
    for(;i<=1000;i++)tmp[i]=0;
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
        }
        link(s0,q);
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
