#include<stdio.h>
int p[362880],q[362880][3][3],p1[362880],
    dx[]={1,0,-1,0},dy[]={0,-1,0,1},
    use[9],map[3][3],num[3][3]=
    {
        {40320,5040,720},
        {120,24,6},
        {2,1,0},
    };
char a[]="urdl";
void up(int s[3][3],int x,int y)
{
    s[x][y]=s[x+1][y];
    s[x+1][y]=0;
}
void down(int s[3][3],int x,int y)
{
    s[x][y]=s[x-1][y];
    s[x-1][y]=0;
}
void left(int s[3][3],int x,int y)
{
    s[x][y]=s[x][y+1];
    s[x][y+1]=0;
}
void right(int s[3][3],int x,int y)
{
    s[x][y]=s[x][y-1];
    s[x][y-1]=0;
}
void (*act[])(int [3][3],int,int)={up,right,down,left},
(*act2[])(int [3][3],int,int)={down,left,up,right};
int copy(int s1[3][3],int s2[3][3],int s)
{
    int i,j,x,y;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            s2[i][j]=s1[i][j];
            if(s1[i][j]==0)
                x=i,y=j;
        }
    if(x+dx[s]>2 || x+dx[s]<0 || y+dy[s]>2 || y+dy[s]<0)
        return 0;
    (*act[s])(s2,x,y);
    return 1;
}
int calc(int s[3][3])
{
    int i,j,k,l,sum=0;
    for(k=0;k<9;k++)
        use[k]=1;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            for(k=l=0;k<s[i][j];k++)
                l+=use[k];
            use[map[i][j]]=0;
            sum+=l*num[i][j];
        }
    return sum;
}
void dfs(int k)
{
    if(p[k]==-2)return;
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
            if(map[i][j]==0)
                break;
        if(map[i][j]==0)
            break;
    }
    (*act2[p[k]])(map,i,j);
    dfs(calc(map));
    putchar(a[p[k]]);
}
main()
{
    int i,j,k,l,t;
    char s[10];
    for(i=0;i<326880;i++)
        p[i]=-1;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            q[0][i][j]=i*3+j+1;
    q[0][2][2]=0;
    p[calc(q[0])]=-2;
    for(i=0,j=1;i<j;i++){
        for(k=0;k<4;k++)
            if(copy(q[i],q[j],k))
            {
                l=calc(q[j]);
                if(p[l]==-1)
                    p[l]=k,j++,p1[l]=i;
            }
    }
    scanf("%d",&t);
    while(t--)
    {
        for(i=0;i<3;i++){
            for(j=0;j<3;j++)
            {
                scanf("%s",s);
                if(s[0]=='x')
                    map[i][j]=0;
                else
                    map[i][j]=s[0]-'0';
            }
        }
        k=calc(map);
        dfs(k);
        puts("");
    }
}
