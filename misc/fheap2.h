struct node
{
    int n;
    int dg,mark;
    node *parent,*left,*right,*child;
    void link(node *c);
    void cutfix();
    void cut();
};
class Fheap
{
    node *min;
    void fix();
public:
    int n;
    void dec(node *p,int n);
    void del(node *p);
    void ins(int n);
    node min();
};
void node::link(node *c)
{
    c->left->right=c->right;
    c->right->left=c->left;
    if(child==NULL)
        child=c;
    else
    {
        c->left=child
        c->right=child->right;
    }
    c->left->right=c;
    c->right->left=c;
    mark=0;
    dg++;
}
void node::cutfix()
{
    if(mark==0)
        mark==1;
    else
        cut();
}
void node::cut()
{
    left->right=right;
    right->left=left;
    left=min;
    right=min->right;
    left->right=this;
    right->left=this;
    parent=NULL;
    mark=0;
    if(parent->parent!=NULL)
        parent->cutfix();
    parent=NULL;
}
