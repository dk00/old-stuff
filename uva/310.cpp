#include<cstdio>
template<class t> class bst
{
public:
    struct node
    {
        t s;
        int h;
        node *left,*right;
        void clear()
        {
            if(left)
                left->clear(),delete left;
            if(right)
                right->clear(),delete right;
        }
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
            ptr=new node;
            ptr->s=a,ptr->h=0,ptr->left=ptr->right=NULL;
            return 1;
        }
        int tmp;
        if(a<ptr->s)
        {
            ptr->h-=(tmp=ins(a,ptr->left));
            if(ptr->h==-2)
            {
                ptr->h=0;
                if(ptr->left->s<a)
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
    void clear()
    {
        if(root)
        {
            root->clear();
            delete root;
        }
        root=NULL;
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

class string
{
public:
    char s[30];
    char& operator[](int n){return s[n];}
    bool operator<(string a)
    {
        int i;for(i=0;s[i] && a.s[i] && s[i]==a.s[i];i++);
        return s[i]<a.s[i];
    }
    bool operator==(string a)
    {
        for(int i=0;s[i] && a.s[i];i++)
            if(s[i]!=a.s[i])
                return 0;
        return 1;
    }
    bool compare(int p,string a)
    {
        int i,j;
        for(i=p,j=0;s[i]&a.s[j] && s[i]==a.s[j];i++,j++);
        return a.s[j]>0;
    }
    void replace(int st,int ed,string a)
    {
        int i,j;
        char tmp[30];
        for(i=j=0;i<st;i++,j++)
            tmp[j]=s[i];
        for(i=0;a.s[i];i++,j++)
            tmp[j]=a.s[i];
        for(i=ed+1;s[i];i++,j++)
            tmp[j]=s[i];
        tmp[j]=0;
        for(i=0;tmp[i];i++)
            s[i]=tmp[i];
        s[i]=0;
    }
    int length(){int i;for(i=0;s[i];i++);return i;}
}a,b,st,ed;
int l1,l2;
bst<string> S;
void go(string s)
{
    if(s.length()>15 || S.find(s))return;
    S.ins(s);
    string t;
    for(int i=0;s[i];i++)
    {
        t=s;
        if(s[i]=='a')
            t.replace(i,i,a);
        else
            t.replace(i,i,b);
        go(t);
    }
}
main()
{
    while(scanf("%s %s %s %s",a.s,b.s,st.s,ed.s)==4)
    {
        S.clear();
        go(st);
        if(S.find(ed))puts("YES");
        else puts("NO");
    }
}
