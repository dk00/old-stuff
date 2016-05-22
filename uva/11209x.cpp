#include <stdio.h>
#include <queue>
#include <algorithm>
using namespace std;
int n,cst,ced,mn,pe[1000],cases=1;
class point { public:int st,ed,v; }edge[3000];
class node
{
public:
    int p,dis,step,used[205];
    bool operator <(node x)const
    {
        if(dis>x.dis) return 1;
        return 0;
    }
}mid[10000];
bool comp(point a,point b)
{
    if(a.st==b.st)
        return a.ed<b.ed;
    return a.st<b.st;
}
void print(node st,node ed)
{
    printf("Case %d: %d\n",cases++,st.dis);
    printf("%d %d",st.step+1,cst);
    int i,j;
    for(i=1;i<=st.step;i++)
        for(j=1;j<=n;j++)
            if(st.used[j]==i)
                printf(" %d",j);
    puts("");
    printf("%d %d",ed.step+1,ced);
    for(i=1;i<=ed.step;i++)
        for(j=1;j<=n;j++)
            if(ed.used[j]==i)
                printf(" %d",j);    
    puts("");
}
bool find(node x)
{
    int i,j;
    for(i=0;i<mn;i++)
        if(x.p==mid[i].p)   
        {
            for(j=1;j<=n;j++)
                if( x.used[j] && mid[i].used[j] && j!=x.p)
                    break;
            if(j>n)
            {
                print(mid[i],x);
                return 1;
            }
        }
    return 0;
}

void bfs(node st,node ed)
{
    priority_queue<node> st_qe, ed_qe;
    node stp, edp, tmp;
    
    st.used[st.p]=ed.used[ed.p]=-1;
    st_qe.push(st), ed_qe.push(ed);
    
    int i,j,k;
    for(k=0, mn=0;;k++, mn=0)
    {
        if(st_qe.empty()  || ed_qe.empty() ) break;
        while(st_qe.top().dis==k && !st_qe.empty() )
        {
            stp=st_qe.top();
            for(i=pe[stp.p-1];i<pe[stp.p];i++)
                if(!stp.used[edge[i].ed])
                {
                    tmp=stp;
                    tmp.p=edge[i].ed;
                    tmp.dis+=edge[i].v;
                    tmp.step=stp.step+1;
                    tmp.used[edge[i].ed]=stp.step+1;
                    st_qe.push(tmp);
                }        
            mid[mn++]=stp;
            st_qe.pop();
        }
        while(ed_qe.top().dis==k && !ed_qe.empty() )
        {
            edp=ed_qe.top();
            for(i=pe[edp.p-1];i<pe[edp.p];i++)
                if(!edp.used[edge[i].ed])
                {
                    tmp=edp;
                    tmp.p=edge[i].ed;
                    tmp.dis+=edge[i].v;
                    tmp.step=edp.step+1;
                    tmp.used[edge[i].ed]=edp.step+1;
                    ed_qe.push(tmp);
                }        
            if(find(edp))
                return;
            ed_qe.pop();
        }
/*
        printf("%d %d\n",st_qe.top().dis,ed_qe.top().dis);
        getchar();
*/
    }
}


main()
{
    int m,i,j,k,v;
/*    freopen("Q11209.in","r",stdin);
    freopen("Q11209.out","w",stdout);*/
    while(scanf("%d",&n)!=EOF && n)
    {
        scanf("%d %d %d",&m,&cst,&ced);
        printf("%d %d %d %d\n",n,m,cst,ced);
        for(k=0;m;m--)
            scanf("%d %d %d",&i,&j,&v),
            edge[k++]=(point){i,j,v}, 
            edge[k++]=(point){j,i,v};
        sort(edge,edge+k,comp);
        for(i=0;i<k;i++)
            pe[edge[i].st]++;
        for(i=1;i<=n;i++)
            pe[i]+=pe[i-1];
        if(cases!=1) puts("");
        puts("begin");
        bfs((node){cst,0,0,0},(node){ced,0,0,0});
        puts("end");
        for(i=0;i<=n;i++)
            pe[i]=0;
    }
}

/*
4 4 1 4
1 2 1
2 3 1
3 4 2
1 3 1
4 5 1 4
1 2 2
1 3 5
2 3 4
2 4 1
3 4 1
5 6 1 5
1 2 3
2 3 4
3 4 4
4 5 3
1 3 1
3 5 2
0
*/
