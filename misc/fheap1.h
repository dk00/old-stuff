#include<stdio.h>
struct node{
    int n;
    int dg,mark;
    node *left,*right,*parent,*child;
    void link(node *c);
    void cut();
    void ccut();
};
class Fheap{
    node *min,*a[100];
    void set();
public:
    void insert(int s);
    void deckey(node *p,int s);
    int extmin();
};
void node::link(node *c){
    c->left->right=c->right;
    c->right->left=c->left;
    if(child==NULL)child=c;
    c->left=child;
    c->right=child->right;
    c->left->right=c;
    c->right->left=c;
    c->parent=this;
}
void node::cut(){
    node *prt=parent;
    if(this==left && this==right)
        parent->child=NULL;
    else{
        left->right=right;
        right->left=left;
    }
    parent=NULL;
    mark=0;
}
void node::ccut(){
    if(parent){
        if(mark){
            this->cut();
            parent->ccut();
        }
        else mark=1;
    }
}
void Fheap::set(){
    int i,d;
    node *ptr,*tmp;
    for(i=0;i<20;i++)a[i]=NULL;
    a[min->dg]=min;
    for(ptr=min->right;ptr!=min;ptr=ptr->right){
        d=ptr->dg;
        while(a[d]){
            if(ptr->n>a[d]->n)
                tmp=ptr,ptr=a[d],a[d]=tmp;
            ptr->link(a[d]);
            a[d++]=NULL;
        }
        a[d]=ptr;
    }
    min=NULL;
    for(i=0;i<20;i++)
        if(a[i] && (!min || min->n>a[i]->n))
            min=a[i];
}
void Fheap::insert(int s){
}
