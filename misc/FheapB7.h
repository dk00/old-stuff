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
            ptr=min->right,min->right=min->child->right,
            min->child->right=ptr;
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
