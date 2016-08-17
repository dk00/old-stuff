#include<cstdio>
#include"FheapB7.h"
Fheap heap;
node now,*v[20000];
struct edge
{
    int v,d;
    edge *next;
}*list[20000];
void free(int n)
{
    int i;
    edge *ptr,*tmp;
    for(int i=0;i<n;i++)
    {
        v[i]=0;
        if(!list[i])
            continue;
        ptr=list[i]->next;
        list[i]->next=0;
        while(ptr)
        {
            tmp=ptr,ptr=ptr->next;
            delete tmp;
        }
        list[i]=0;
    }
    while(heap.n>0)heap.extractmin();
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
    int i,j,k,n,m,s,t,T,C=1;
    freopen("10986.in","r",stdin);
    edge *ptr;
    for(i=0;i<20000;i++)list[i]=0;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d %d",&n,&m,&s,&t);
        free(n);
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            if(i==j)continue;
            insert(i,j,k);
            insert(j,i,k);
        }
        printf("Case #%d: ",C++);
        v[s]=heap.insert(0,s);
        for(i=0;i<n;i++)
            if(i!=s)
                v[i]=heap.insert(200000001,i);
        while(heap.n)
        {
            now=heap.extractmin();
            v[now.v]=0;
            if(now.v==t)break;
            if(!list[now.v])continue;
            ptr=list[now.v];do
            {
                if(v[ptr->v] && now.d+ptr->d<v[ptr->v]->d)
                    v[ptr->v]->decrease(now.d+ptr->d,&heap.min);
                ptr=ptr->next;
            }while(ptr!=list[now.v]);
        }
        if(now.v==t && now.d<200000001)
            printf("%d\n",now.d);
        else
            puts("unreachable");
    }
}
