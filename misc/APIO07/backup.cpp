#include<cstdio>
template<class x>inline void swap(x &a,x &b){x c=a;a=b,b=c;}
int n,hn,p[200000],c[200000];
struct node
{
    int l,r,c1,c2;
    bool operator<(node a)const
    {
        if(l<0 || r>=n)return 0;
        if(a.l<0 || a.r>=n)return 1;
        return c2-c1<a.c2-a.c1;
    }
    void link(int u){p[l]=p[r]=u;}
}s[200000];
void swap(node s[],int a,int b)
{
    node tmp=s[a];
    s[a]=s[b];
    s[b]=tmp;
    s[a].link(a),s[b].link(b);
}
void ins_heap(node s[],int &n,node a)
{
    s[n]=a;
    s[n].link(n);
    int i=n++;
    while(i>0 && s[i]<s[i/2])
        swap(s,i,i/2),i/=2;
}
node pop_heap(node s[],int& n)
{
    swap(s,--n,1);
    int i,j;
    for(i=1;i*2<n;i=j)
    {
        if(i*2+1>=n || s[i*2]<s[i*2+1])
            j=i*2;
        else
            j=i*2+1;
        if(s[j]<s[i])swap(s,i,j);
        else break;
    }
    return s[n];
}
node pop_heap(node s[],int& n,int v)
{
    while(v/2>0)
        swap(s,v,v/2),v/=2;
    return pop_heap(s,n);
}
void combine(node &a,node b,int mi)
{
    a.c1+=b.c1,a.c2+=b.c2;
    a.l<?=b.l,a.r>?=b.r;
}
int go()
{
    node tmp,a=pop_heap(s,hn);
    int c0=a.c2-a.c1;
    swap(a.c1,a.c2);
    a.l--;
    if(a.l>=0 && p[a.l])
    {
        tmp=pop_heap(s,hn,p[a.l]);
        combine(a,tmp,a.l);
    }
    a.r++;
    if(a.r<n && p[a.r])
    {
        tmp=pop_heap(s,hn,p[a.r]);
        combine(a,tmp,a.r);
    }
    ins_heap(s,hn,a);
    printf("%d %d %d\n",a.l,a.r,c0);
    return c0;
}
main()
{
    int i,j;
    while(scanf("%d %d",&n,&j)==2)
    {
        hn=1;
        for(i=0;i<n;i++)
            scanf("%d",c+i);
        for(i=0,n--;i<n;i++)
        {
            c[i]=c[i+1]-c[i];
            ins_heap(s,hn,(node){i,i,0,c[i]});
        }
        for(i=0;j--;i+=go());
        printf("%d\n",i);
    }
}
