#include<cstdio>
const int dx[]={1,2,1,2,-1,-2,-1,-2},dy[]={2,1,-2,-1,2,1,-2,-1};
int n,map[50][50],dg[50][50];
void setdg()
{
    int i,j,k,px,py;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            map[i][j]=0,dg[i][j]=0;
            for(k=0;k<8;k++){
                px=i+dx[k],py=j+dy[k];
                if(px<n && px>=0 && py<n && py>=0)
                    dg[i][j]++;
            }
        }
}
void mark(int x,int y,int de)
{
    int i;
    for(i=0;i<8;i++)
        if(x+dx[i]>=0 && x+dx[i]<n && y+dy[i]>=0 && y+dy[i]<n
        && map[x+dx[i]][y+dy[i]]==0)
            dg[x+dx[i]][y+dy[i]]+=de;
}
int go(int x,int y,int s[])
{
    int i,j,k=0,tmp,num[8];
    for(i=0;i<8;i++)
        if(x+dx[i]>=0 && x+dx[i]<n && y+dy[i]>=0 && y+dy[i]<n
        && map[x+dx[i]][y+dy[i]]==0)
        {
            s[k++]=i;
            num[i]=dg[x][y];
        }
    for(i=0;i<k;i++)
        for(j=1;j<k;j++)
            if(num[j-1]>num[j])
            {
                tmp=num[j-1],num[j-1]=num[j],num[j]=tmp;
                tmp=s[j-1],s[j-1]=s[j],s[j]=tmp;
            }
    return k;
}
int dfs(int d,int x,int y)
{
    mark(x,y,-1);
    map[x][y]=d;
    if(d==n*n)
        return 1;
    int i,k,s[8];
    k=go(x,y,s);
    for(i=0;i<k;i++)
        dfs(d+1,x+dx[s[i]],y+dy[s[i]]);
    map[x][y]=0;
    mark(x,y,1);
}
main()
{
    int i,j;
    while(scanf("%d",&n)==1)
    {
        if(n<=0 || n>=50)break;
        setdg();
        if(dfs(0,0,1))
            for(i=0;i<n;i++)
            {
                for(j=0;j<n;j++)
                {
                    if(n*n<10)
                        printf("%2d",map[i][j]);
                    else if(n*n<100)
                        printf("%3d",map[i][j]);
                    else if(n*n<1000)
                        printf("%4d",map[i][j]);
                    else
                        printf("%5d",map[i][j]);

                }
                puts("");
            }
        else
            puts("Can't find Knight tour.");
    }
}
