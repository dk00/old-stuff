#include<cstdio>
#include<cstdlib>
const int dx[]={1,1,-1,-1,2,2,-2,-2},dy[]={2,-2,2,-2,1,-1,1,-1};
int n,step,map[51][51],num[51][51];
int min(int a,int b){return a<b?a:b;}
struct move
{
    int d,sc1,sc2,sc3;
    int operator-(move a)
    {
        if(sc1==a.sc1)
        {
            if(sc2==a.sc2)
                return -sc3-a.sc3;
            return sc2-a.sc2;
        }
        return sc1-a.sc1;
    }
};
int movecmp(const void *a,const void *b)
{
    return *(move *)a-*(move *)b;
}
bool able(int x,int y)
{
    return(x>=0 && x<n && y>=0 && y<n);
}
bool go(int x,int y)
{
    map[x][y]=step++;
    if(step>n*n)
        return 1;
    int k,l,r,nx,ny,mn=0;
    move test[8];
    for(k=0;k<8;k++)
    {
        nx=x+dx[k],ny=y+dy[k];
        if(able(nx,ny))
        {
            num[nx][ny]--;
            if(map[nx][ny]==0)
            {
                test[mn].d=k;
                test[mn].sc1=num[nx][ny];
                test[mn].sc2=0;
                for(l=0;l<8;l++)
                {
                    if(!able(nx+dx[l],ny+dy[l]))
                        continue;
                    for(r=l;r<8;r++)
                        if(able(nx+dx[l]+dx[r],ny+dy[l]+dy[r]) &&
                        (nx+dx[l]+dx[r]!=x || ny+dy[l]+dy[r]!=y))
                            test[mn].sc2++;
                }
                r=(n-1)/2;
                test[mn++].sc3=(nx-r)*(nx-r)+(ny-r)*(ny-r);
            }
        }
    }
    qsort(test,mn,sizeof(test[0]),movecmp);
    for(k=0;k<mn;k++)
        if(go(x+dx[test[k].d],y+dy[test[k].d]))
            return 1;
    for(k=0;k<8;k++)
    {
        nx=x+dx[k],ny=y+dy[k];
        if(able(nx,ny))
            num[nx][ny]++;
    }
    step--;
    map[x][y]=0;
    return 0;
}
main()
{
    int i,j,k,x,y;
    while(scanf("%d %d %d",&n,&x,&y)==3)
    {
        if(n<6 || n%2)
        {
            puts("No Circuit Tour.\n");
            continue;
        }
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                for(k=map[i][j]=num[i][j]=0;k<8;k++)
                    if(able(i+dx[k],j+dy[k]))
                        num[i][j]++;
        step=1;
        go(x-1,y-1);
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
                printf("%5d",map[i][j]);
            puts("");
        }
        puts("");
    }
}
