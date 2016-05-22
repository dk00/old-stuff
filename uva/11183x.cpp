#include<cstdio>
const int V=1001;
struct E{short s,t,c;}c[50000];
int n,to[V],help[V],back[V],pre[V];
char u[50000];
int d[V],p[V],p0[V];
int find(int v)
{
    if(p[v]==v)return v;
    return(p[v]=find(p[v]));
}
void uni(int a,int b)
{
    a=find(a),b=find(b);
    if(d[a]<d[b])p[a]=b;
    else p[b]=a;
    if(d[a]==d[b])d[a]++;
}
void clear(){for(int i=0;i<n;i++)p[i]=i,d[i]=0;}
void backup(){for(int i=0;i<n;i++)p0[i]=p[i];}
void recover(){for(int i=0;i<n;i++)p[i]=p0[i];}
main()
{
    int i,j,k,m,sum,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        clear();
        for(i=0;i<m;i++)
        {
            scanf("%d %d %d",&c[i].s,&c[i].t,&c[i].c),u[i]=1;
            if(c[i].s==c[i].t || c[i].t==0)i--,m--;
        }//Discard the edges entering the root or itself
        printf("Case #%d: ",C++);
        if(m==0)
        {
            if(n>1)puts("Possums!");
            else puts("0");
            continue;
        }
        for(j=k=sum=0;m>0;m=j,j=1)
        {   //Select min-cost entering edge for every node
            for(i=0;i<n;i++)to[i]=-1,help[i]=0;
            for(i=0;i<m;i++)
               if(to[c[i].t]<0 || c[i].c<c[to[c[i].t]].c)
                    to[c[i].t]=i;
            for(i=0;k>=0 && i<n;i++)//Check if every node have entering node
                if(i!=k && p[i]==i && to[i]<0)k=-1;
            if(k<0)break;
            backup();
            for(i=j=0;i<n;i++)
                if(to[i]>=0)
                {
                    if(find(c[to[i]].s)==find(c[to[i]].t))
                        help[i]=1,j++; //Mark cycles
                    else uni(c[to[i]].s,c[to[i]].t);
                    sum+=(back[c[to[i]].t]=c[to[i]].c);
                    pre[c[to[i]].t]=c[to[i]].s;
                }
            if(!j)break;
            recover();
            for(i=0;i<n;i++)
                if(help[i]) //Merging cycles
                    while(find(i)!=find(pre[i]))
                        uni(i,pre[i]),i=pre[i];
            k=find(k);
            for(i=0;i<m;i++)
                if(u[i])
                {   //Reassign edge weight
                    c[i].c-=back[c[i].t];
                    c[i].s=find(c[i].s),c[i].t=find(c[i].t);
                    if(c[i].s==c[i].t)u[i]=0;
                }   //Discard inner edges
            for(i=j=0;i<m;i++)
                if(u[i])c[j]=c[i],u[j++]=1;
        }
        if(k<0 || j)puts("Possums!");
        else printf("%d\n",sum);
    }
}
