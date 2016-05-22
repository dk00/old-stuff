struct node{
    int dg,n,v,q,able;
    node *parent,*child,*left,*right;
}now;
class Fheap{
public:
    int n;
    node *min,*rootlist[100000];
    Fheap();
    void link(node *p,node *c);
    void consolidate();
    node extractmin();
    void insert(int n,int v,int q,int able);
    void cut(node *p,node *c);
};
Fheap::Fheap(){
    n=0;
    min=NULL;
}
void Fheap::link(node *p,node *c){
    c->left->right=c->right;
    c->right->left=c->left;
    if(p->child!=NULL){
        c->left=p->child;
        c->right=p->child->right;
        p->child->right=c;
        c->right->left=c;
    }
    else p->child=c->left=c->right=c;
    c->parent=p;
    p->dg++;
}
void Fheap::consolidate(){
node *a[30],*ptr=min,*tmp;
int i,d;
    for(i=0;i<30;i++)a[i]=NULL;
    for(i=0,ptr=min;!i || ptr!=min;ptr=ptr->right)
        rootlist[i++]=ptr;
    while(i--){
        ptr=rootlist[i];
        d=ptr->dg-1;
        while(a[++d]!=NULL && a[d]!=ptr){
            if(ptr->n>=a[d]->n){
                tmp=a[d];
                a[d]=ptr;
                ptr=tmp;
            }
            if(a[d]==min)min=ptr;
            link(ptr,a[d]);
            a[d]=NULL;
        }
        a[d]=ptr;
        ptr=ptr->right;
    }
    for(i=0;a[i]==NULL;i++);
    min=a[i];
    min->right=min;
    min->left=min;
    min->parent=NULL;
    for(i++;i<30;i++)
        if(a[i]!=NULL){
            a[i]->parent=NULL;
            a[i]->right=min->right;
            a[i]->left=min;
            min->right=a[i];
            a[i]->right->left=a[i];
            if(min->n>a[i]->n)min=a[i];
        }
}
node Fheap::extractmin(){
    node *z,*ptr,*tmp;
    z=min;
    ptr=min->child;
    n--;
    if(ptr==NULL){
        if(n){
            min->left->right=min->right;
            min->right->left=min->left;
            min=min->right;
            consolidate();
        }
        else
            min=NULL;
        return *z;
    }
    while(ptr!=ptr->right){
        ptr->right->left=ptr->left;
        ptr->left->right=ptr->right;
        tmp=ptr->right;
        ptr->right=min->right;
        min->right=ptr;
        ptr->left=min;
        ptr->right->left=ptr;
        ptr=tmp;
    };
    ptr->left=min;
    ptr->right=min->right;
    min->right=ptr;
    ptr->right->left=ptr;
    min->left->right=min->right;
    min->right->left=min->left;
    min=min->right;
    consolidate();
    return *z;
}
void Fheap::insert(int n,int v,int q,int able){
    node *x=new node;
    x->n=n;
    x->v=v;
    x->q=q;
    x->able=able;
    x->parent=x->child=NULL;
    x->dg=0;
    if(min==NULL){
        min=x;
        x->right=x->left=x;
    }
    else{
        x->right=min->right;
        min->right=x;
        x->left=min;
        x->right->left=x;
        if(min->n>x->n)min=x;
    }
    this->n++;
}
