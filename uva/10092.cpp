#include<stdio.h>
const int inf=20000000;
#define MaxV 1022
struct list{
    int v;
    list *prev,*next;
}*head;
int t,h[MaxV],e[MaxV],ne[MaxV],c[MaxV][MaxV];
inline int min(int a,int b)
{
    if(a<b)
        return a;
    return b;
}
void inline makelist()
{
    int i;
    list *ptr;
    /*if(head!=NULL)
    {
        ptr=head->next;
        while(ptr!=NULL && ptr->next!=NULL)
            delete ptr->prev;
        if(ptr!=NULL)
            delete ptr;
    }*/
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
void inline tofront(list *v)
{
    v->prev->next=v->next;
    if(v->next!=NULL)
        v->next->prev=v->prev;
    v->next=head;
    head->prev=v;
    v->prev=NULL;
    head=v;
}
void inline push(int v,int u)
{
    int f=min(c[v][u],e[v]);
    e[v]-=f;
    e[u]+=f;
    c[v][u]-=f;
    c[u][v]+=f;
}
void inline relabel(int v)
{
    int i,min;
    for(i=0,min=2*t;i<=t;i++)
        if(c[v][i]>0 && h[i]+1<min)
            min=h[i]+1;
    h[v]=min;
}
void inline discharge(int v)
{
    while(e[v]>0)
    {
        if(ne[v]>t)
        {
            relabel(v);
            ne[v]=0;
        }
        else if(c[v][ne[v]]>0 && h[v]==h[ne[v]]+1)
            push(v,ne[v]);
        else
            ne[v]++;
    }
}
int inline flow()
{
    int i,v,lh;
    list *ptr;
    for(i=0;i<=t;i++)
    {
        h[i]=0;
        e[i]=c[0][i];
        c[0][i]-=e[i];
        c[i][0]+=e[i];
    }
    h[0]=t+1;
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
main()
{
    int i,j,k,nk,np,sum;
    while(1)
    {
        scanf("%d %d",&nk,&np);
        if(nk==0 && np==0)
            break;
        t=nk+np+1;
        for(i=1;i<=t;i++)
            for(j=1;j<=t;j++)
                c[i][j]=0;
        for(i=1,sum=0;i<=nk;i++)
        {
            scanf("%d",&c[0][i]);
            sum+=c[0][i];
        }
        for(j=1;j<=np;j++)
        {
            c[nk+j][t]=1;
            scanf("%d",&k);
            while(k--)
            {
                scanf("%d",&i);
                c[i][nk+j]=1;
            }
        }
        if(sum<=np && flow()==sum)
        {
            puts("1");
            for(i=1;i<=nk;i++)
            {
                for(j=1,k=0;j<=np;j++)
                    if(c[nk+j][i])
                    {
                        if(k)putchar(' ');
                        else k=1;
                        printf("%d",j);
                    }
                puts("");
            }
        }
        else
            puts("0");
    }
}
