template<class t> class bst
{
public:
    struct node
    {
        t s;
        int num;
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
    bool find(t a)
    {
        return(search(a,root)!=NULL);
    }
    void ins(t a,node **ptr=NULL)
    {
        if(ptr==NULL)
        {
            ins(a,&root);
            return;
        }
        if(*ptr==NULL)
        {
            *ptr=new node(a,1,NULL,NULL);
            //**ptr=(node){a,1,NULL,NULL};
            return;
        }
        if(a<(*ptr)->s)
            ins(a,&(*ptr)->left),(*ptr)->num++;
        else
            ins(a,&(*ptr)->right);
    }
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
        {
            tmp->num--;
            tmp=tmp->left;
        }
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
        if(n==ptr->num)
            return ptr->s;
        if(n<ptr->num)
            return nth(n,ptr->left);
        return nth(n-ptr->num,ptr->right);
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
