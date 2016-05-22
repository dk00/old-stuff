#include<cstdio>
int d1[20000],d2[20000];
struct edge
{
    int v,d;
    edge *next;
}*list[20000],*ptr,*tmp;
struct dlist
{
    int v;
    dlist *prev,*next;
    void move(dlist *to)
    {
        prev->next=next,next->prev=prev;
        next=to,prev=to->prev;
        prev->next=this,next->prev=this;
    }
    void ins(int nv)
    {
        next->prev=new dlist;
        *next->prev=(dlist){nv,nd,this,next};
        next=next->prev;
    }
}*q[50002],*v[20000];
void free(int n,int m)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(!list[i])continue;
        ptr=list[i]->next;
        list[i]->next=0;
        while(ptr)
        {
            tmp=ptr,ptr=ptr->next;
            delete tmp;
        }
        list[i]=0;
    }
    for(i=0;i<=m+1;i++)
    {
        if(!q[i])continue;
        ptr=q[i]->next;
        while(ptr)
        {
            tmp=ptr,ptr=ptr->next;
            delete tmp;
        }
        q[i]=0;
    }
}
void insert(int a,int b,int c)
{
    edge *ptr=new edge;
    *ptr=(edge){b,c,ptr};
    if(!list[a])list[a]=ptr;
    else
    {
        ptr->next=list[a]->next;
        list[a]->next=ptr;
    }
}
main()
{
    int i,j,k,n,m,s,t,T,C=1,max,a;
    //freopen("10986.in","r",stdin);
    for(i=0;i<20000;i++)list[i]=0;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d %d",&n,&m,&s,&t);
        free(n);
        for(i=0,max=20000;i<n;i++)
            d1[i]=0,d2[i]=m+1;
        for(a=0;a<m;a++)
        {
            scanf("%d %d %d",&i,&j,&k);
            if(i==j)continue;
            insert(i,j,k);
            insert(j,i,k);
            if(max>k)max=k;
        }
        for(k=15;max>>(k-1)==0;k--);
        while(k--)
        {
            for(i=0;i<n;i++)
            {
                d2[i]=m+1;
                v[i]=new dlist;
                *v[i]=(dlist){i,v[i],v[i]};
                if(q[i])v[i]->move(q[i]);
                else q[i]=v[i];
            }
            d2[s]=0;
            q[0]=new dlist;
            *q[0]=(dlist){s,0,q[0],q[0]};
            for(i=0;i<m+1;i++)
            {
                while(q[i])
                {
                    ptr=q[i];
                    if(ptr->next==ptr)q[i]=0;
                    tmp=list[ptr->v];do{
                        now=i+tmp->d<-d1[ptr->v]+d1[tmp->v];
                        if(now<d2[tmp->v])
                            move(q[d2[tmp->v],q[now];

                    }while(tmp!=list[ptr->v]);
                }
            }
        }
        printf("Case #%d: ",C++);
    }
}
