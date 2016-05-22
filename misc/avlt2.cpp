#include<cstdio>
template<class t> class avl
{
    struct node{t s; int d; node *left,*right;} *root;
    node *&search(t a,node *ptr)
    {
        if(ptr==NULL || a==ptr->s)
            return ptr;
        if(a<ptr->s)
            return search(a,ptr->left);
        return search(a,ptr->right);
    }
    node *&find(t a){return search(a,root);}
    void rotate(node *&ptr,int s)
    {
        node **u[][2]={{&ptr->rihgt,&ptr->right->left},
        {&ptr->left,&ptr->left->right}},*tmp=*u[s][1];
        *u[s][1]=ptr,ptr=*u[s][0],*u[s][0]=tmp;
    }
    int ins(t a,node *&ptr)
    {
        if(ptr==NULL)
        {
            ptr=new node;
            *ptr=(node){a,0,NULL,NULL};
            return 1;
        }
        int sw=(a<ptr->s);
        node **u[]={&ptr->right,&ptr->left},*&nptr=u[sw];
        ptr->d+=ins(a,nptr)*(1-sw*2);
        if(ptr->d/2)
        {
            ptr->d=(nptr->d)=0;
            if((a<nptr->s)^sw)
                rotate(nptr,!sw);
            rotate(ptr,sw);
        }
        return(ptr->d!=0);
    }
    void ins(t a){ins(a,root);}
    int suc(node *&ptr1,node *&ptr2)
    {
        if(ptr2->left==NULL)
        {
            ptr1->a=ptr2->a;
            return 1;
        }
        ptr2->d+=suc(ptr1,ptr2->left);
        if(ptr2->d/2)
        {
            ptr2->d=ptr2->right->d,ptr2->right->d=0;
            if(ptr2->d*ptr->right->d<0)
                rotate(ptr2->right,1);
            rotate(ptr2,0);
        }
        return(ptr2->d==0);
    }
    int del(t a,node *&ptr)
    {
        int sw=(a<ptr->s);
        node **u[]={&ptr->right,&ptr->left},*&nptr=*u[sw];
        if(ptr->s==a)
            ptr->d-=suc(ptr,ptr->right);
        else
            ptr->d-=del(a,nptr)*(1-sw*2);
        if(ptr->d/2)
        {
            ptr->d=nptr->d,nptr->d=0;
            if(ptr->d*nptr->d<0)
                rotate(*u[sw],!sw);
            rotate(ptr,sw);
        }
        return(ptr->d==0);
    }
    void del(t a){del(a,root);}
};
main()
{
}
