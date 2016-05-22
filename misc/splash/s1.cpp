#include<cstdio>
#include<cstdlib>
#include"sclass1.h"
Heap heap;
P test,best,tp[20];
const int bound=4;
int dfs(int n,int x,int y)
{
    int i,j,now,min=10000;
    if(tp[n].calc()<best.score)
        best=tp[n];
    if(n==1)
    {
        for(i=0;i<6;i++)
            for(j=0;j<6;j++)
                if(tp[1].s[i][j]==4)
                {
                    tp[0]=tp[1];
                    tp[0].add(i,j);
                    now=tp[0].calc();
                    if(tp[0].num==0 && tp[0]<best)best=tp[0];
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
                if(now<min)min=now;
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
        /*open(test);
        node=20;
        while(heap.n>1 && heap.n<9000 && node--)
            open(heap.exmin());*/
        best.set();
        best.score=2147483647;
        // Greedy Search
        /*while(test.num>0)
        {
            best.set();
            best.score=2147483647;
            if(best.pn>0)
            {
                test.add(best.path[0].x,best.path[0].y);
                printf("%d %d\n",best.path[0].x+1,best.path[0].y+1);
            }*/

        tp[5]=test;
        dfs(5,0,0);
        //}
        //----------------------------------------------------------------
        best.print();
    }
}
