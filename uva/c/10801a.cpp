const int heapsize=25;
struct node{
    int key;
    int dg,mark;
    node *parent,*child,*left,*right;
    void link(node *c);
    void cut();
    void cascadingcut();
};
class fheap{
    node *min,*nodelist[heapsize];
    int n;
    void consolidate();
    node extractmin();
    void insert(int key);
    void decreasekey(node *s,int key);
};
void node::link(node *c){
    c->parent=this;
    if(child==NULL){
        child=c;
        return;
    }
    c->right=child;
    c->left=child->left;
    child=c;
    child->left->right=c;
    child->left=c;
    dg++;
    mark=0;
}
void node::cut(){
    if(parent->child==this){
        if(left!=s)parent->child=left;
        else if(right!=this)parent->child=right;
        else parent->child=NULL;
    }
    right=min;
    left=min->left;
    parent=NULL;
    parent->dg--;
    min->left->right=this;
    min->left=this;
    mark=0;
}
void node::cascadingcut(){
    if(parent!=NULL)
        if(mark){
            node *ptr=parent;
            cut();
            ptr->cascadingcut();
        }
        else mark=1;
}
