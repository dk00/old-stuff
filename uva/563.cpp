#include<cstdio>
int n,m,b1[]={2,4,8,16},b2[]={32,64,128,512},
    dx[]={1,0,-1,0},dy[]={0,1,0,-1};
bool inline able(int x,int y)
{
    return(x>=0 && x<n && y>=0 && y<m);
}
bool findpath(int x,int y,int d)
{
    if(d && !x || x==n-1 || !y || y==m-1)
        return true;
    int i;
    if(d)               //out node
    {
        if(v[x][y]&1 && findpath(x,y,0))
        {
            v[x][y]&=~1;
            return true;
        }
        for(i=0;i<4;i++)
            if(v[x][y]&b2[i] &&  able(x+dx[i],y+dy[i]) &&
            findpath(x+dx[i],y+dy[i],0))
            {
                v[x][y]&=~b2[i];
                v[x+dx[i]][y+dy[i]]|=b1[i];
                return true;
            }
    }
    else    //in node
    {
        if(v[x][y]%2==0 && findpath(x,y,1))
        {
            v[x][y]|=1;
            return true;
        }
        for(i=0;i<4;i++)
            if(v[x][y]&b1[i] && able(x+dx[i],y+dy[i] &&
            findpath(x+dx[i],y+dy[i],1))
            {
                v[x][y]&=~b1[i];
                v[x+dx[i]][y+dy[i]]|=b2[i];
                return true;
            }
    }
    return false;
}
main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d %d",&n,&m,&p);
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                map[i][j]=0,v[i][j]=960;
        while(p--)
        {
            scanf("%d %d",&i,&j);
            map[i-1][j-1]=1;
            v[i-1][j-1]|=1;
        }
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
                if(map[i][j] && !findpath(i,j,1))
                    break;
            if(j<m)break;
        }
        if(i<n)
            puts("not possible");
        else
            puts("possible");
    }
}
/*
v uldr uldr
*/
