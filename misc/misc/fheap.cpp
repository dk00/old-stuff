class node{
public:
    int n,dg;
    node *left,*right,*parent,*child;
    void link(node *c);
};
class fheap{
public:
    node *min,*root[18];
    void set();
    void insert(int n);
    node exmin();
}heap;
void node::link(node *c){
    if(child==NULL)
        child=c;
    else{
        child->right=c;
        child->right->left=c;
    }
    c->left->right=c->right;
    c->right->left=c->left;
    c->left=child;
    c->right=child->right;
}
void fheap::set(){
    int i,nd;
    node *ptr,*ptr1,*tmp,*d[18];
    root[0]=min;
    for(i=0;i<18;i++)d[i]=NULL;
    for(i=1,ptr=min->right;ptr!=min;ptr=ptr->right,i++)
        root[i]=ptr;
    while(i--){
        ptr=root[i];
        nd=ptr->dg;
        while(d[nd]!=NULL){
            ptr1=d[nd];
            if(ptr->n<ptr1->n){
                tmp=ptr;
                ptr=ptr1;
                ptr1=tmp;
            }
            ptr->link(ptr1);
            nd++;
        }
        d[nd]=ptr;
    }
    min=NULL;
    for(i=0;d[i]==NULL;i++);
    min=d[i];
    min->left=min;
    min->right=min;
    for(i++;i<18;i++)
        if(d[i]!=NULL){
            d[i]->right=min->right;
            d[i]->left=min;
            d[i]->left->right=d[i];
            d[i]->right->left=d[i];
            if(d[i]->n<min->n)
                min=d[i];
        }
}
void fheap::insert(int n){
    node *ptr=new node;
    ptr->n=n;
    ptr->dg=0;
    ptr->parent=NULL;
    ptr->child=NULL;
    if(min==NULL){
        min=ptr;
        min->left=min;
        min->right=min;
    }
    else{
        ptr->left=min;
        ptr->right=min->right;
        ptr->left->right=ptr;
        ptr->right->left=ptr;
        if(n<min->n)
            min=ptr;
    }
}
node fheap::exmin(){
    node ptr=*min;
    if(min->right==min){
        delete min;
        min=NULL;
        return ptr;
    }
    min->right->left=min->left;
    min->left->right=min->right;
    delete min;
    min=ptr.right;
    set();
    return ptr;
}
