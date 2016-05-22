#include<cstdio>
const int dx[]={1,2,2,1,-1,-2,-2,-1},dy[]={2,1,-1,-2,-2,-1,1,2};
struct node
{
    int x,y,k;
}stack[2500];
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
int able(int x,int y,int k)
{
    x+=dx[k],y+=dy[k];
    if(x>=0 && x<n && y>=0 && y<n)
        return 1;
    return 0;
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
        if(able(x,y,i) && map[x+dx[i]][y+dy[i]]==0)
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
main()
{
    int i,j,top,found;
    node now;
    while(scanf("%d",&n)==1)
    {
        if(n<=0 || n>=50)break;
        setdg();
        top=0;
        now.x=n-1;
        now.y=n-1;
        now.k=-1;
        found=0;
        while(top>=0)
        {//void dfs(int d,int x,int y)
        // if(d>=n*n) return 1;
            if(top==n*n-1)
            {
                found=1;
                map[now.x][now.y]=top+1;
                break;
            }
        // for(int i=0;i<8;i++)
        //      if(dfs(d+1,x+dx[i],y+dy[i])==1)
            if(now.k+1<8)
            {
                if(able(now.x,now.y,now.k+1)==0)
                    continue;
                now.k++;
                stack[top++]=now;
                map[now.x][now.y]=top;
                mark(now.x,now.y,-1);
                now.x+=dx[now.k];
                now.y+=dy[now.k];
                now.k=-1;
            }
            else
            {
                map[now.x][now.y]=0;
                mark(now.x,now.y,1);
                if(top<=0)
                    break;
                now=stack[--top];
            }
        //          return 1;
        //return 0;
        }
        if(found)
            for(i=0;i<n;i++)
            {
                for(j=0;j<n;j++)
                    printf("%3d",map[i][j]);
                puts("");
            }
        else
            puts("Can't find Knight tour.");
    }
}
