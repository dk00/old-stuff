#include<cstdio>
struct path
{
    int a,b,c,d;
}p[100];
int n,bound,next,score,s1[10][10],s2[10][10];
int sta[65536];
int calc()
{
    int i,num=0;;
    for(i=0;i<n*n;i++)
    {
        num<<=1;
        num|=s1[i/n][i%n];
    }
    return num;
}
int count(int x,int y)
{
    return (x>0 && s1[x-1][y])+(y>0 && s1[x][y-1])+
           (x<n-1 && s1[x+1][y])+(y+1<n && s1[x][y+1]);
}
bool go(int d)
{
    int i=d+score;
    if(i>bound)
    {
        if(next==bound || i<next)
            next=i;
        return 0;
    }
    if(!score)
        return 1;
    i=calc();
    if(!sta[i] || d<=sta[i])
        sta[i]=d;
    else return 0;
    int j,k,l;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            p[d].a=i,p[d].b=j;
            if(s1[i][j])
            {
                s1[i][j]--;
                if(!s2[i][j])score--;
                for(k=0;k<n;k++)
                    for(l=0;l<n;l++)
                        if(i!=k && j!=l && !s1[k][l] && count(k,l)>1)
                        {
                            p[d].c=k,p[d].d=l;
                            if(d && i==p[d-1].c && j==p[d-1].d &&
                            k==p[d-1].a && l==p[d-1].b)continue;
                            if(!s2[k][l])score++;
                            s1[k][l]++;
                            if(go(d+1))
                                return 1;
                            s1[k][l]--;
                            if(!s2[k][l])score--;
                        }
                if(!s2[i][j])score++;
                s1[i][j]++;
            }
        }
    sta[calc()]=0;
    return 0;
}
main()
{
    int i,j;
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                scanf("%d",&s1[i][j]);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                scanf("%d",&s2[i][j]);
        for(i=score=0;i<n;i++)
            for(j=0;j<n;j++)
                if(s2[i][j] && !s1[i][j])
                    score++;
        next=score;
        do{
            bound=next;
        }while(!go(0));
        for(i=0;i<bound;i++)
            printf("(%d,%d) (%d,%d)\n",p[i].a,p[i].b,p[i].c,p[i].d);
    } 
}
