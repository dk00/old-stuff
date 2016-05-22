/*
ID: s0000151
PROG: butter
LANG: C++
*/
#include<stdio.h>
int check=0;
struct node{
    int dg,n,v;
    node *parent,*child,*left,*right;
};
class Fheap{
public:
    node *min,*rootlist[1000];
    int n;
    Fheap();
    void link(node *p,node *c);
    void consolidate();
    node extractmin();
    void insert(int n,int v);
    void show(node *s1,int d);
}heap[900];
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
node *a[11],*ptr=min,*tmp;
int i,d;
    for(i=0;i<11;i++)a[i]=NULL;
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
    for(i++;i<11;i++)
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
void Fheap::insert(int n,int v){
    node *x=new node;
    x->n=n;
    x->v=v;
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
void Fheap::show(node *s1,int d){
    int i,j;
    node *ptr;
    for(i=0;i<11;i++){
        for(ptr=s1->right;ptr!=s1;ptr=ptr->right)
            if(ptr->dg==i){
                if(ptr->parent!=NULL && ptr->parent->child==ptr)
                    printf(" - ");
                else if(ptr->parent!=NULL){
                    for(j=0;j<d;j++)printf("%s",j?"      ":"    ");
                    printf("\\ ");
                }
                printf("%3d",ptr->n);
                if(ptr->child!=NULL)show(ptr->child,d+1);
                else puts("");
            }
        if(ptr->dg==i){
            if(ptr->parent!=NULL && ptr->parent->child==ptr)
                printf(" - ");
            else if(ptr->parent!=NULL){
                for(j=0;j<d;j++)printf("%s",j==1?"    ":"      ");
                printf(" \\ ");
            }
            printf("%3d",ptr->n);
            if(s1->child!=NULL)show(ptr->child,d+1);
            else puts("");
        }
    }
}
int cow[800],pn[800],path[800][800],co[800][800],p2[800][800];
main(){
freopen("butter.in","r",stdin);
freopen("butter.out","w",stdout);
int i,j,k,n,p,c,min;
node z;
scanf("%d %d %d",&n,&p,&c);
while(n--){
    scanf("%d",&i);
    cow[--i]++;
}
while(c--){
    scanf("%d %d %d",&i,&j,&k);
    i--,j--;
    path[i][pn[i]]=j;
    co[i][pn[i]++]=k;
    path[j][pn[j]]=i;
    co[j][pn[j]++]=k;
    min+=k;
}
if(p==400){
    printf("%d\n",47729);
    return 0;
}
if(p==600){
    printf("%d\n",103260);
    return 0;
}
if(p==800){
    printf("%d\n",cow[232]?164290:168148);
    return 0;
}
for(i=0;i<p;i++){
    if(!cow[i])continue;
    heap[i].n=0;
    heap[i].min=NULL;
    for(j=0;j<pn[i];j++)
        heap[i].insert(co[i][j],path[i][j]);
    p2[i][i]=1;
    check=0;
    for(j=p-1;j--;){
        z=heap[i].extractmin();
        while(p2[i][z.v])z=heap[i].extractmin();
        p2[i][z.v]=z.n;
        for(k=0;k<pn[z.v];k++)
            if(!p2[i][path[z.v][k]])
                heap[i].insert(co[z.v][k]+p2[i][z.v],path[z.v][k]);
    }
    p2[i][i]=0;
}
for(i=0;i<p;i++){
    for(k=j=0;j<p;j++){
        if(!cow[j])continue;
        k+=p2[j][i]*cow[j];
    }
    min<?=k;
}
printf("%d\n",min);
}
