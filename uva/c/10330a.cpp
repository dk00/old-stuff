#include<stdio.h>
const int inf=20000000;
#define MaxV 205
struct list{
    int v;
    list *prev,*next;
}*head;
int t,h[205],e[205],ne[205],c[205][205];
void makelist(){
    list *ptr=new list;
    (head=ptr)->prev=ptr->next=NULL;
    for(int i=1;i<t-1;i++,ptr=ptr->next)
        ((ptr->next=new list)->prev=ptr)->v=i;
    ptr->v=t-1;
    ptr->next=NULL;
}
void tofront(list *v){
    if(v->prev->next=v->next)
        v->next->prev=v->prev;
    (head=(v->next=head)->prev=v)->prev=NULL;
}
void push(int v,int u){
    int f=(c[v][u]<?e[v]);
    e[v]-=f;
    e[u]+=f;
    c[v][u]-=f;
    c[u][v]+=f;
}
void relabel(int v){
    int i,min;
    for(i=t+1,min=2*t;i--;)
        if(c[v][i])
            min<?=(h[i]+1);
    h[v]=min;
    ne[v]=0;
}
void discharge(int v){
    while(e[v]){
        if(ne[v]>t)relabel(v);
        else if(c[v][ne[v]] && h[v]==h[ne[v]]+1)push(v,ne[v]);
        else ne[v]++;
    }
}
int flow(){
    int i,v,lh;
    list *ptr;
    for(i=0;i<=t;i++){
        h[i]=0;
        e[i]=c[0][i];
        c[0][i]-=e[i];
        c[i][0]+=e[i];
    }
    h[0]=t+1;
    makelist();
    for(ptr=head;ptr;ptr=ptr->next){
        lh=h[v=ptr->v];
        discharge(v);
        if(h[v]>lh && head!=ptr)tofront(ptr);
    }
    return e[t];
}
main()
{
    int i,j,k,n,m;
    while(scanf("%d",&n)!=EOF)
    {
        t=n*2+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                c[i][j]=0;
        for(i=1;i<=n;i++)
            scanf("%d",&c[i][i+n]);
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            c[n+i][j]+=k;
        }
        scanf("%d %d",&i,&j);
        while(i--)
        {
            scanf("%d",&k);
            c[0][k]=inf;
        }
        while(j--)
        {
            scanf("%d",&k);
            c[n+k][t]=inf;
        }
        printf("%d\n",flow());
    }
}
