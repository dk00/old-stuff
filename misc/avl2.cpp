template<class t>class avl
{
    struct node
    {
        t s;
        int d;
        node *left,*right;
    }*root;
    node *&search(t a,node *&ptr)
    {
        if(ptr==NULL || a==ptr->s)
            return ptr;
        if(a<ptr->s)
            return search(a,ptr->left);
        return search(a,ptr->right);
    }
    bool find(t a){return search(a,root);}
    int ins(t a,node *&ptr)
    {
        if(ptr==NULL)
        {
            ptr=new node;
            *ptr=(node){a,0,NULL,NULL};
            return 1;
        }
        if(a<ptr->s)
        {
            ptr->d-=ins(a,ptr->left);
            if(ptr->d==-2)
            {
                ptr->d=ptr->left->d=0;
                if(ptr->left->s<a)
                    rotate(ptr->left,0);
                rotate(ptr,1);
            }
        }
        else
        {
            ptr->d+=ins(a,ptr->right);
            if(ptr->d==2)
            {
                ptr->d=ptr->right->d=0;
                if(a<ptr->right->s)
                    rotate(ptr->right,1);
                rotate(ptr,0);
            }
        }
        return ptr->d!=0;
    }
    void ins(t a){ins(a,root);}
    
}
