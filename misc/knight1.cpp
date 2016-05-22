#include<cstdio>
const int dx[]={1,2,2,1,-1,-2,-2,-1},dy[]={2,1,-1,-2,-2,-1,1,2};
struct node
{
    int x,y,n,k,s[8];
    void go();
}stack[2500];
int bn,map[50][50],dg[50][50];
void setdg()
{
    int i,j,k,px,py;
    for(i=0;i<bn;i++)
        for(j=0;j<bn;j++){
            map[i][j]=0,dg[i][j]=0;
            for(k=0;k<8;k++){
                px=i+dx[k],py=j+dy[k];
                if(px<bn && px>=0 && py<bn && py>=0)
                    dg[i][j]++;
            }
        }
}
void mark(int x,int y,int de)
{
    int i;
    for(i=0;i<8;i++)
        if(x+dx[i]>=0 && x+dx[i]<bn && y+dy[i]>=0 && y+dy[i]<bn
        && map[x+dx[i]][y+dy[i]]==0)
            dg[x+dx[i]][y+dy[i]]+=de;
}
void node::go()
{
    int i,j,tmp,num[8];
    for(i=n=0;i<8;i++)
        if(x+dx[i]>=0 && x+dx[i]<bn && y+dy[i]>=0 && y+dy[i]<bn
        && map[x+dx[i]][y+dy[i]]==0)
        {
            s[n]=i;
            num[n++]=dg[x+dx[i]][y+dy[i]];
        }
    for(i=0;i<n;i++)
        for(j=1;j<n;j++)
            if(num[j-1]>num[j])
            {
                tmp=num[j-1],num[j-1]=num[j],num[j]=tmp;
                tmp=s[j-1],s[j-1]=s[j],s[j]=tmp;
            }
}
main()
{
    int i,j,top,found;
    node now;
    while(scanf("%d",&bn)==1)
    {
        if(bn<=0 || bn>=50)break;
        setdg();
        top=0;
        now.x=0;
        now.y=0;
        now.k=-1;
        now.go();
        found=0;
        while(top>=0)
        {
            if(top==bn*bn-1)
            {
                found=1;
                map[now.x][now.y]=top+1;
                break;
            }
            if(now.k+1<now.n)
            {
                now.k++;
                stack[top++]=now;
                map[now.x][now.y]=top;
                mark(now.x,now.y,-1);
                now.x+=dx[now.s[now.k]];
                now.y+=dy[now.s[now.k]];
                now.k=-1;
                now.go();
            }
            else
            {
                map[now.x][now.y]=0;
                mark(now.x,now.y,1);
                if(top<=0)
                    break;
                now=stack[--top];
            }
        }
        if(found)
        for(i=0;i<bn;i++)
        {
            for(j=0;j<bn;j++)
            {
                if(bn*bn<10)
                    printf("%2d",map[i][j]);
                else if(bn*bn<100)
                    printf("%3d",map[i][j]);
                else if(bn*bn<1000)
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
