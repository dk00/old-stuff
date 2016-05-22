const int MaxV=200;
struct list{
    int v;
    list *prev,*next;
}*head;
int t,h[MaxV],e[MaxV],n[MaxV],c[MaxV][MaxV];
inline int min(int a,int b)
{
    if(a<b)
        return a;
    return b;
}
void makelist()
{
    int i;
    list *ptr;
    head=new list;
    head->prev=head->next=NULL;
    ptr=head;
    for(i=1;i<t-1;i++,ptr=ptr->next)
    {
        ptr->v=i;
        ptr->next=new list;
        ptr->next->prev=ptr;
    }
    ptr->v=t-1;
    ptr->next=NULL;
}
void tofront(list *v)
{
    v->prev->next=v->next;
    if(v->next!=NULL)
        v->next->prev=v->prev;
    v->next=head;
    head->prev=v;
    v->prev=NULL;
    head=v;
}
void push(int v,int u)
{
    int f=min(c[v][u],e[v]);
    e[v]-=f;
    e[u]+=f;
    c[v][u]-=f;
    c[u][v]+=f;
}
void relabel(int v)
{
    int i,min;
    for(i=0,min=2*t;i<=t;i++)
        if(c[v][i]>0 && h[i]+1<min)
            min=h[i]+1;
    h[v]=min;
}
void discharge(int v)
{
    while(e[v]>0)
    {
        if(n[v]>t)
        {
            relabel(v);
            n[v]=0;
        }
        else if(c[v][n[v]]>0 && h[v]==h[n[v]]+1)
            push(v,n[v]);
        else
            n[v]++;
    }
}
int flow()
{
    int i,v,lh;
    list *ptr;
    for(i=0;i<=t;i++)
    {
        if(c[0][i]==0)
            continue;
        e[i]=c[0][i];
        c[0][i]-=e[i];
        c[i][0]+=e[i];
    }
    h[0]=t+1;
    if(head==NULL)
        makelist();
    for(ptr=head;ptr!=NULL;ptr=ptr->next)
    {
        v=ptr->v;
        lh=h[v];
        discharge(v);
        if(h[v]>lh && head!=ptr)
            tofront(ptr);
    }
    return e[t];
}
