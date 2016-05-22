#include<cstdio>
#include<cstdlib>
#include"sclass1.h"
Heap heap;
P test,best,tp[20];
const int bound=4;
int rx,ry,nlv;
int dfs(int n,int x,int y)
{
    int i,j,now,min=10000;
    if(n==1)
    {
        for(i=0;i<6;i++)
            for(j=0;j<6;j++)
                if(tp[1].s[i][j]==4)
                {
                    tp[0]=tp[1];
                    tp[0].add(i,j);
                    now=tp[0].remain();
                    if(tp[0].num==0 && tp[0].pn<best.pn)
                        best=tp[0];
                    if(now<min)min=now;
                }
        return min;
    }
    for(i=0;i<6;i++)
        for(j=0;j<6;j++)
        {
            if(i<x || i==x && j<y)
                continue;
            if(tp[n].s[i][j] && tp[n].s[i][j]<4)
            {
                tp[n-1]=tp[n];
                tp[n-1].add(i,j);
                now=dfs(n-1,i,j);
                if(now<min)
                {
                    min=now;
                    if(n==nlv)
                        rx=i,ry=j;
                }
            }
        }
    return min;
}
int node;
void open(P root)
{
    if(root.ball<=0 || root.pn>8)
        return;
    if(root.num<=0)
    {
        if(root.ball>best.ball)
            best=root;
        return;
    }
    int i,j,l,min,now;
    for(l=1;l<=bound;l++)
    {
        tp[l]=root;
        dfs(l,0,0);
    }
    for(i=0;i<6;i++)
        for(j=0;j<6;j++)
            if(root.s[i][j] && root.s[i][j]<4)
            {
                tp[15]=root;
                tp[15].add(i,j);
                min=tp[15].calc();
                heap.insert(tp[15]);
            }
}
main()
{
    int n,l;
    while(1)
    {
        q1=_q[0],q2=_q[1];
        heap.n=1;
        test.set();
        test.get();
        scanf("%d",&n);
        test.ball=n;
        best.num=best.pn=200;
        /*open(test);
        node=20;
        while(heap.n>1 && heap.n<9000 && node--)
            open(heap.exmin());*/
        for(l=1;l<=70;l++)
        {
            tp[l]=test;
            nlv=l;
            dfs(l,0,0);
            if(best.num==0)break;
        }
        best.print();
        if(best.pn==200)
            printf("%d %d\n",rx+1,ry+1);
    }
}
