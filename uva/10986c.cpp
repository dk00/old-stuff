#include<cstdio>
struct node
{
    int v,d;
    bool operator<(node a){return d<a.d;}
}now;
struct List
{
    int v,d;
    List *next;
}*ptr,*tmp,*list[20000];
template<class t> class Heap
{
public:
    int n;
    t s[100000];
    Heap(){n=1;}
    int insert(t a)
    {
        s[n]=a;
        int i=n++;
        while(i>0 && s[i]<s[i/2])
            s[0]=s[i],s[i]=s[i/2],s[i/2]=s[0],i/=2;
        return i;
    }
    t min()
    {
        s[0]=s[1],s[1]=s[--n];
        int i=1;
        while(i*2<n)
        {
            if(i*2+1>=n || s[i*2]<s[i*2+1])
            {
                if(s[i*2]<s[i])
                    s[n]=s[i*2],s[i*2]=s[i],s[i]=s[n],i=i*2;
                else break;
            }
            else if(s[i*2+1]<s[i])
                s[n]=s[i*2+1],s[i*2+1]=s[i],s[i]=s[n],i=i*2+1;
            else break;
        }
        return s[0];
    }
    void decrease(int p,t a)
    {
        s[p]=a;
        while(p && s[p]<s[p/2])
            s[0]=s[p],s[p]=s[p/2],s[p/2]=s[0],p/=2;
    }
};

Heap<node> heap;
int d[20000],v[20000];
main()
{
    int i,j,k,n,m,s,t,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d %d",&n,&m,&s,&t);
        for(i=0;i<n;i++)
        {
            d[i]=-1,heap.n=1;
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
        v[s]=heap.insert((node){s,0});
        while(heap.n>1)
        {
            now=heap.min();
            if(now.v==t)break;
            for(ptr=list[now.v];ptr;ptr=ptr->next)
            {
                if(d[ptr->v]<0)
                {
                    d[ptr->v]=d[now.v]+ptr->d;
                    v[ptr->v]=heap.insert((node){ptr->v,d[ptr->v]});
                }
                else if(v[now.v] && d[now.v]+ptr->d<d[ptr->v])
                {
                    d[ptr->v]=d[now.v]+ptr->d;
                    heap.decrease(v[ptr->v],(node){ptr->v,d[ptr->v]});
                }
            }
            v[now.v]=0;
        }
        printf("Case #%d: ",C++);
        if(d[t]>=0)printf("%d\n",d[t]);
        else puts("unreachable");
    }
}
