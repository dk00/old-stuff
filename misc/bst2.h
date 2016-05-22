const int bi[]={0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80,0x100,0x200,
    0x400,0x800,0x1000,0x2000,0x4000,0x8000,
    0x10000,0x20000,0x40000,0x80000,0x100000,0x200000,0x400000,0x800000,
    0x1000000,0x2000000,0x4000000,0x8000000,
    0x10000000,0x20000000,0x40000000,0x80000000};
class bst
{
public:
    struct node
    {
        int a,b,n;
        node *s[2];
    }*root,*path[33];
    int ins(node *&ptr,int a,int b,int d=31)
    {
        if(!ptr)
        {
            ptr=new node;
            ptr->n=0,ptr->s[0]=ptr->s[1]=0;
        }
        if(d>=0)
            return ins(ptr->s[(a&bi[d])>0],a,b,d-1);
        ptr->a=a,ptr->b=b;
        return ptr->n++;
    }
    void clear(node *&ptr)
    {
        if(ptr)
        {
            clear(ptr->s[0]),clear(ptr->s[1]);
            delete ptr,ptr=NULL;
        }
    }
    node *find(node *ptr,int a,int d=31)
    {
        path[d+1]=ptr;
        if(ptr==NULL || d<0)
            return ptr;
        node *tmp;
        if((tmp=find(ptr->s[(a&bi[d])>0],a,d-1)))
            return tmp;
        else if(a&bi[d] || !ptr->s[1])
            return NULL;
        ptr=ptr->s[1];
        while(d--){
            path[d]=ptr;
            if(ptr->s[0])ptr=ptr->s[0];
            else ptr=ptr->s[1];
        }
        return ptr;
    }
    void del(int a,int b)
    {
        int d;
        a=find(root,a)->a;
        while(a<=b)
        {
            for(d=0;d<32;d++)
            {
                if(path[d]->s[0] || path[d]->s[1])
                    break;
                if(path[d+1]->s[0]==path[d])
                    path[d+1]->s[0]=0;
                else path[d+1]->s[1]=0;
                n-=path[d]->n;
                delete path[d];
            }
            a=find(root,a)->a;
        }
    }
    int n;
    bst(){n=0;root=0;}
    void clear(){n=0;clear(root);}
    int insert(int a,int b){n++;return ins(root,a,b);}
    node *find(int a){return find(root,a);}
    void remove(int a,int b){del(a,b);}
};
