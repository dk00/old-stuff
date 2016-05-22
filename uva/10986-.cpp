#include<cstdio>
#include"FheapB7.h"
node now,*v[20000];
struct List
{
    int v,d;
    List *next;
}*ptr,*tmp,*list[20000];
Fheap heap;
int d[20000];
main()
{
    //freopen("10986.in","r",stdin);
    int i,j,k,n,m,s,t,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d %d",&n,&m,&s,&t);
        for(i=0;i<n;i++)
        {
            d[i]=-1;
            if(!list[i])continue;
            for(ptr=list[i];ptr;)
            {
                tmp=ptr,ptr=ptr->next;
                delete tmp;
            }
            v[i]=0,list[i]=0;
        }
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            if(i==j)continue;
            ptr=new List,*ptr=(List){j,k,0};
            if(!list[i])list[i]=ptr;
            else ptr->next=list[i]->next,list[i]->next=ptr;
            ptr=new List,*ptr=(List){i,k,0};
            if(!list[j])list[j]=ptr;
            else ptr->next=list[j]->next,list[j]->next=ptr;
        }
        d[s]=0;
        v[s]=heap.insert(0,s);
        int pass=0;
        while(heap.n>0)
        {
            now=heap.extractmin();
            for(ptr=list[now.v];ptr;ptr=ptr->next)
            {
                if(d[ptr->v]<0)
                {
                    d[ptr->v]=d[now.v]+ptr->d;
                    v[ptr->v]=heap.insert(d[ptr->v],ptr->v);
                }
                else if(d[now.v]+ptr->d<d[ptr->v])
                {
                    d[ptr->v]=d[now.v]+ptr->d;
                    v[ptr->v]->decrease(d[ptr->v],&heap.min);
                }
            }
            v[now.v]=0;
        }
        printf("Case #%d: ",C++);
        if(d[t]>=0)printf("%d\n",d[t]);
        else puts("unreachable");
    }
}
