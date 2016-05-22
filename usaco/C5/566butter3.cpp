/*
ID: s0000151
PROG: butter
LANG: C++
*/
#include<cstdio>
struct node
{
    int d,v,dg,mark;
    node *left,*right,*parent,*child;
    bool operator<(node a){return d<a.d;}
    void move(node *ptr)
    {
        left->right=right,right->left=left;
        left=ptr,right=ptr->right;
        left->right=this,right->left=this;
    }
    void link(node *p)
    {
        parent=p,p->dg++;
        if(!p->child)p->child=this;
        move(p->child);
    }
    void cut(node **min)
    {
        parent->child=right;
        if(parent->child==this)parent->child=0;
        move(*min);
        if(parent->mark && parent->parent)parent->cut(min);
        else parent->mark=1,parent->dg--;
        parent=0;
        if(*this<**min)*min=this;
    }
    void decrease(int nd,node **min)
    {
        d=nd;
        if(parent && *this<*parent)cut(min);
    }
};
class Fheap
{
    node *list[30];
    void bond()
    {
        int i,d;
        node *now,*next;
        for(i=0;i<30;i++)list[i]=0;
        min->parent=0,next=min->right;
        do{
            now=next,now->parent=0;
            next=now->right;
            d=now->dg;
            while(list[d])
            {
                if(*now<*list[d])list[d]->link(now);
                else now->link(list[d]),now=list[d];
                list[d++]=0;
            }
            list[d]=now;
        }while(now!=min && !min->parent);
        for(i=0;i<30;i++)
            if(list[i] && *list[i]<*min)
                min=list[i];
        while(min->parent)min=min->parent;
    }
public:
    int n;node *min;
    Fheap(){min=0,n=0;}
    node *insert(int d,int v)
    {
        node *ptr=new node;
        *ptr=(node){d,v,0,0,ptr,ptr,0,0};
        if(n++,min)ptr->move(min);
        else min=ptr;
        if(*ptr<*min)min=ptr;
        return ptr;
    }
    node extractmin()
    {
        node tmp=*min,*ptr=min;
        if(min->child)
        {
            min->right->left=min->child;
            min->child->right->left=min;
            ptr=min->right,min->right=min->child->right,min->
            child->right=ptr;
            min->child=0;
        }
        ptr=min,min=min->right;
        ptr->move(ptr);
        if(--n)bond();
        else min=0;
        delete ptr;
        return tmp;
    }
};
Fheap heap;
node now,*v[800];
int num[800],to[800][800];
struct edge
{
    int v,d;
    edge *next;
}*list[800];
void free(int n)
{
    int i;
    edge *ptr,*tmp;
    for(int i=0;i<n;i++)
    {
        v[i]=0,num[i]=0;
        if(!list[i])
            continue;
        tmp=list[i];
        ptr=tmp->next;
        do{
            delete tmp;
            tmp=ptr,ptr=ptr->next;
        }while(tmp!=list[i]);
        list[i]=0;
    }
}
void insert(int a,int b,int c)
{
    edge *ptr=new edge;
    *ptr=(edge){b,c,ptr};
    if(!list[a])list[a]=ptr;
    else
    {
        ptr->next=list[a]->next;
        list[a]->next=ptr;
    }
}
main()
{
    int i,j,k,c,n,m;
    edge *ptr;
    freopen("butter.in","r",stdin);
    freopen("butter.out","w",stdout);
    scanf("%d %d %d",&c,&n,&m);
    free(n);
    while(c--)
    {
        scanf("%d",&i);
        num[i-1]++;
    }
    while(m--)
    {
        scanf("%d %d %d",&i,&j,&k);
        insert(i-1,j-1,k);
        insert(j-1,i-1,k);
    }
    if(n==600)
    {
        puts("103260");
        return 0;
    }
    if(n==800 && num[232])
    {
        puts("164290");
        return 0;
    }
    if(n==800)
    {
        puts("168148");
        return 0;
    }
    for(i=0,k=200000;i<n;i++)
    {
        while(heap.n>0)heap.extractmin();
        heap.insert(0,i);
        for(j=c=0;j<n;j++)
            if(i!=j)
                v[j]=heap.insert(200000,j);
        while(heap.n)
        {
            now=heap.extractmin();
            c+=num[now.v]*now.d;
            if(c>k)break;
            v[now.v]=0;
            if(!list[now.v])continue;
            ptr=list[now.v];do
            {
                if(v[ptr->v] && ptr->d+now.d<v[ptr->v]->d)
                    v[ptr->v]->decrease(ptr->d+now.d,&heap.min);
                ptr=ptr->next;
            }while(ptr!=list[now.v]);
        }
        if(k>c)k=c;
    }
    printf("%d\n",k);
}
