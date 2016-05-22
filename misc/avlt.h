template<class t> class bst
{
public:
    struct node
    {
        t s;
        int h;
        node *left,*right;
    }*root;
    bst(){root=NULL;};
    node *&search(t a,node *&ptr)
    {
        if(ptr==NULL || (ptr)->s==a)
            return ptr;
        if(a<(ptr)->s)
            return search(a,(ptr)->left);
        return search(a,(ptr)->right);
    }
    bool find(t a){return(search(a,root)!=NULL);}
    void rotate(node *&ptr,int k)
    {
        if(k)
        {
            node *tmp=ptr->right->left;
            ptr->right->left=ptr;
            ptr=ptr->right;
            ptr->left->right=tmp;
        }
        else
        {
            node *tmp=ptr->left->right;
            ptr->left->right=ptr;
            ptr=ptr->left;
            ptr->right->left=tmp;
        }
    }
   int ins(t a,node *&ptr)
    {
        if(ptr==NULL)
        {
            ptr=new node,*ptr=(node){a,0,NULL,NULL};
            return 1;
        }
        int tmp;
        if(a<ptr->s)
        {
            ptr->h-=(tmp=ins(a,ptr->left));
            if(ptr->h==-2)
            {
                ptr->h=0;
                if(a>ptr->left->s)
                {
                    ptr->left->right->h=-ptr->left->h;
                    ptr->left->h=0;
                    rotate(ptr->left,1);
                }
                ptr->h=ptr->left->h=0;
                rotate(ptr,0);
                return 0;
            }
        }
        else
        {
            ptr->h+=(tmp=ins(a,ptr->right));
            if(ptr->h==2)
            {
                ptr->h=0;
                if(a<ptr->right->s)
                {
                    ptr->right->left->h=-ptr->right->h;
                    ptr->right->h=0;
                    rotate(ptr->right,0);
                }
                ptr->h=ptr->right->h=0;
                rotate(ptr,1);
                return 0;
            }
        }
        return tmp;
    }
    void ins(t a){ins(a,root);}
    void del(node *&ptr)
    {
        if(ptr->left==NULL)
        {
            ptr=ptr->right;
            return;
        }
        if(ptr->right==NULL)
        {
            ptr=ptr->left;
            return;
        }
        node *&tmp=ptr->right;
        while(tmp->left!=NULL)
            tmp=tmp->left;
        ptr->s=tmp->s;
        del(tmp);
    }
    void del(t a)
    {
        node *&ptr=search(a,root);
        if(ptr!=NULL)del(ptr);
    }
    t nth(int n,node *ptr=NULL)
    {
        if(ptr==NULL)
            ptr=root;
        if(n==ptr->h)
            return ptr->s;
        if(n<ptr->h)
            return nth(n,ptr->left);
        return nth(n-ptr->h,ptr->right);
    }
    void show(node *ptr=NULL)
    {
        if(ptr==NULL)
        {
            show(root);
            return;
        }
        printf("%d",ptr->s);
        if(ptr->left==NULL && ptr->right==NULL)
            return;
        printf(" (");
        if(ptr->left)
            show(ptr->left);
        printf(") ");
        printf("(");
        if(ptr->right)
            show(ptr->right);
        printf(") ");
    }
};
