#include<stdio.h>
#include<math.h>
struct node{
    int dg,key;
    node *parent,*child,*left,*right;
};
class Heap{
    int n;
    node *min;
    Heap();
    friend void link(node *p,node *c);
    void fix();
    void insert(int n);
    void insert(node *x);
    node extractmin();
};
Heap::Heap(){
    n=0;
    min=NULL;
}
void link(node *p,node *c){
    c->left->right=c->right;
    c->right->left=c->left;
    if(p->child==NULL){
        p->child=c;
        c->left=c;
        c->right=c;
    }
    else{
        c->left=p->child;
        c->right=p->child->right;
        c->left->right=c;
        c->right->left=c;
    }
    p->dg++;
}
void Heap::fix(){
    int i,d,lv=ceil(log2(n));
    node ,*ptr=min,*tmp,*rootlist[MAX],**a=malloc(sizeof(node)*lv);
    for(i=0;i<lv;i++)a[i]=NULL;
    for(i=0,ptr=min;!i || ptr!=min;ptr=ptr->right,i++)
        rootlist[i]=ptr;
    while(i--){
        ptr=rootlist[i];
        d=ptr->dg-1;
        while(a[++d]!=NULL){
            if(ptr->key>a[d]->key){
                tmp=a[d];
                a[d]=ptr;
                ptr=tmp;
            }
            link(ptr,a[d]);
            a[d]=NULL;
        }
        a[d]=ptr;
    }
    for(i=0;a[i]==NULL;i++);
    min=a[i];
    while(++i<lv)
        if(a[i]!=NULL){
            a[i]->left=min;
            a[i]->right=min->right;
            a[i]->right->left=a[i];
            min->right=a[i];
            if(min->key>a[i]->key)
                min=a[i];
        }
}
void Heap::insert(int n){
    node *x=new node;
    x->key=n;
    x->parent=NULL;
    x->child=NULL;
    x->dg=0;
    if(min==NULL){
        min=x;
        x->left=x;
        x->right=x;
    }
    else{
        x->left=min;
        x->right=x->left->right;
        x->left->right=x;
        x->right->left=x;
    }
}
void Heap::insert(node *x){
    if(min==NULL){
        min=x;
        x->left=x;
        x->right=x;
    }
    else{
        x->left=min;
        x->right=x->left->right;
        x->left->right=x;
        x->right->left=x;
    }
}
node Heap::extractmin(){
    if(n-1){
        if(min->child==NULL){
            min->left->right=min->right;
            min->right->left=min->left;
            return *
        }
    }
}
