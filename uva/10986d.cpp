#include<cstdio>
struct List
{
    int v,d;
    List *next;
}*ptr,*tmp,*list[20000];
struct Dlist
{
    int v,d;
    Dlist *prev,*next;
}*qtr,*q[50002],*v[20005];
int d1[20005],d2[20005];
char err[1000];
void move(Dlist *ptr,int m)
{
    if(m<0)
        puts(err);
    if(ptr->prev)ptr->prev->next=ptr->next;
    if(ptr->next)ptr->next->prev=ptr->prev;
    if(!q[m])
    {
        q[m]=ptr;
        ptr->prev=ptr->next=0;
        return;
    }
    ptr->prev=q[m],ptr->next=q[m]->next;
    ptr->prev->next=ptr;
    if(ptr->next)ptr->next->prev=ptr;
}
inline int rd(int i,int u,int v,int w)
{return (w>>i)+d1[u]*2-d1[v]*2;}
main()
{
    //freopen("10986.in","r",stdin);
    int i,j,k,n,m,s,t,T,nv,nd,max,find,C=1;
    for(i=0;i<20000;i++)
        v[i]=new Dlist;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d %d",&n,&m,&s,&t);
        sprintf(err,"%d %d %d %d",n,m,s,t);
        for(i=max=0;i<n;i++)
        {
            if(!list[i])continue;
            for(ptr=list[i];ptr;)
            {
                tmp=ptr,ptr=ptr->next;
                delete tmp;
            }
            d1[i]=0,list[i]=0;
        }
        for(nv=find=0;nv<m;nv++)
        {
            scanf("%d %d %d",&i,&j,&k);
            ptr=new List,*ptr=(List){j,k,0};
            if(list[i])
                ptr->next=list[i]->next,list[i]->next=ptr;
            else list[i]=ptr;
            ptr=new List,*ptr=(List){i,k,0};
            if(list[j])
                ptr->next=list[j]->next,list[j]->next=ptr;
            else list[j]=ptr;
            if(k>max)max=k;
        }
        for(k=15;max>>(k-1)==0 && k;k--);
        while(k--)
        {
            for(i=0;i<=m+1;i++)q[i]=0;
            for(i=0;i<n;i++)
            {
                d2[i]=m+1;
                *v[i]=(Dlist){i,m+1,0,0};
                move(v[i],m+1);
            }
            v[s]->d=d2[s]=0,move(v[s],0);
            for(i=0;i<m+1;i++)
            {
                if(!q[i])continue;
                for(qtr=q[i];qtr;qtr=qtr->next)
                {
                    q[i]=qtr;
                    nv=qtr->v,nd=qtr->d;
                    if(nv==t)find=1;
                    for(ptr=list[nv];ptr;ptr=ptr->next)
                        if(nd+rd(k,nv,ptr->v,ptr->d)<d2[ptr->v])
                        {
                            d2[ptr->v]=nd+rd(k,nv,ptr->v,ptr->d);
                            v[ptr->v]->d=d2[ptr->v];
                            move(v[ptr->v],d2[ptr->v]);
                        }
                }
            }
            for(i=0;i<n;i++)
                d1[i]=d1[i]*2+d2[i];
        }
        printf("Case #%d: ",C++);
        if(find)printf("%d\n",d1[t]);
        else puts("unreachable");
    }
}
