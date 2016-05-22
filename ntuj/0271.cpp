#include<cstdio>
struct pt
{
    long long s[2];
    pt(){}
    pt(int x)
    {
        s[0]=s[1]=0;
        s[x/64]^=(1ll<<(x%64));
    }
    char operator[](int x){return!!(s[x/64]&(1ll<<(x%64)));}
    void set(int x,char y)
    {
        long long tmp=1ll<<(x%64);
        if(y)s[x/64]|=tmp;
        else s[x/64]&=~tmp;
    }
    pt And(pt x)
    {
        pt tmp=*this;
        tmp.s[0]&=x.s[0];
        tmp.s[1]&=x.s[1];
        return tmp;
    }
    pt Or(pt x)
    {
        pt tmp=*this;
        tmp.s[0]|=x.s[0];
        tmp.s[1]|=x.s[1];
        return tmp;
    }
    pt Or(int y)
    {
        pt tmp=*this;
        tmp.set(y,1);
        return tmp;
    }
    char operator!()const{return!s[0]&&!s[1];}
    char operator<=(pt x)const
    {
        return((s[0]&x.s[0])==s[0] && (s[1]&x.s[1])==s[1]);
    }
    char operator==(pt x)const{return s[0]==x.s[0] && s[1]==x.s[1];}
}c[999];
struct node
{
    node *l,*r;
}*q;
int n,sum=0;
char find(int i,pt x,node *ptr=q)
{
    if(i>=n)return 1;
    if(!ptr)return 0;
    if(!x[i] && find(i+1,x,ptr->r))return 1;
    return find(i+1,x,ptr->l);
}
node *init(node *&ptr)
{
    if(!ptr)
    {
        ptr=new node;
        ptr->l=ptr->r=0;
    }
    return ptr;
}
void ins(pt a)
{
    node *ptr=q;
    for(int i=0;i<n;i++)
    {
        if(a[i])
            ptr=init(ptr->l);
        else
            ptr=init(ptr->r);
    }
}
void clear(node *ptr=q)
{
    if(ptr)
    {
        clear(ptr->l);
        clear(ptr->r);
        delete ptr;
    }
}
void go(int i,pt a,pt b)
{
    if(sum>1000)return;
    pt tmp=b;
    for(int j=0;j<i;j++)
        tmp.set(j,0);
    tmp=tmp.Or(a);
    if(find(0,tmp,q))return;
    int x=1;
    for(int j=0;j<i;j++)
        if(b[j] && a<=c[j])x=0;
    for(;i<n;i++)
        if(b[i] && a<=c[i])
            go(i+1,a.Or(i),b.And(c[i])),x=0;
    /*for(i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(a[i] && a[j] && i!=j && !c[i][j])x=0;*/
    if(x)
    {
        sum++;
        ins(a);
    }
    //if(x)printf(">%d\n",sum);
}
main()
{
    int i,j,m;
    while(scanf("%d %d",&n,&m)==2)
    {
        sum=0;
        q=0;
        init(q);
        for(i=0;i<n;i++)
            c[i].s[0]=c[i].s[1]=0ll;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i-1].set(j-1,1);
            c[j-1].set(i-1,1);
        }
        for(i=0;i<n;i++)
        {
            for(j=0;j<i;j++)
                if(i!=j && !c[i][j])break;
            if(j<i)break;
        }
        if(i>=n)
        {
            puts("1");
            continue;
        }
        sum=0;
        for(i=0;i<n;i++)
            go(i+1,(pt)i,c[i]);
        if(sum>1000)
            puts("Too many maximal sets of friends.");
        else
            printf("%d\n",sum);
        clear();
    }
}
