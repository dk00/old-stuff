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
    void cut(node *&min)
    {
        if(!parent)return;
        parent->child=right;
        if(parent->child==this)parent->child=0;
        move(min);
        if(parent->mark)parent->cut(min);
        else parent->mark=1,parent->dg--;
        parent=0;
        if(*this<*min)min=this;
    }
    void decrease(int nd,node *&min)
    {
        d=nd;
        if(parent){if(*this<*parent)cut(min);}
        else if(*this<*min)min=this;
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

node now,*v[20000];
struct List
{
    int v,d;
    List *next;
}*ptr,*tmp,*list[20000];
Fheap heap;
int d[20000];
main()
{
    //freopen("10986.in","r",stdin);
    int i,j,k,n,m,s,t,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d %d",&n,&m,&s,&t);
        for(i=0;i<n;i++)
        {
            d[i]=-1;
            if(!list[i])continue;
            for(ptr=list[i];ptr;)
            {
                tmp=ptr,ptr=ptr->next;
                delete tmp;
            }
            v[i]=0,list[i]=0;
        }
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            if(i==j)continue;
            ptr=new List,*ptr=(List){j,k,0};
            if(!list[i])list[i]=ptr;
            else ptr->next=list[i]->next,list[i]->next=ptr;
            ptr=new List,*ptr=(List){i,k,0};
            if(!list[j])list[j]=ptr;
            else ptr->next=list[j]->next,list[j]->next=ptr;
        }
        d[s]=0;
        v[s]=heap.insert(0,s);
        int pass=0;
        while(heap.n>0)
        {
            now=heap.extractmin();
            for(ptr=list[now.v];ptr;ptr=ptr->next)
            {
                if(d[ptr->v]<0)
                {
                    d[ptr->v]=d[now.v]+ptr->d;
                    v[ptr->v]=heap.insert(d[ptr->v],ptr->v);
                }
                else if(d[now.v]+ptr->d<d[ptr->v])
                {
                    d[ptr->v]=d[now.v]+ptr->d;
                    v[ptr->v]->decrease(d[ptr->v],heap.min);
                }
            }
            v[now.v]=0;
        }
        printf("Case #%d: ",C++);
        if(d[t]>=0)printf("%d\n",d[t]);
        else puts("unreachable");
    }
}
