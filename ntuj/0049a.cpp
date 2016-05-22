#include<cstdio>
int n,dx[]={1,0,-1,0,0,0},dy[]={0,1,0,-1,0,0},dz[]={0,0,0,0,1,-1};
char map[25][25][25],t[25][25];
void rotate(char s[25][25])
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            t[i][j]=s[i][j];
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            s[i][j]=t[j][n-i-1];
}
void paint0(char s[25][25],int h)
{
    int i,j,k;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            if(s[i][j]=='X')
                map[i][j][h]^=-1;
            if(s[i][j]=='-')
                for(k=0;k<n;k++)
                    map[i][j][k]^=1;
        }
}
char paint1(char s[25][25],int h)
{
    int i,j,k;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            if(s[i][j]=='X' && map[i][h][j]>0)return 0;
            if(s[i][j]!='-')continue;
            for(k=0;k<n;k++)
                if(map[i][k][j]<0)return 0;
        }
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            if(s[i][j]=='X')
                map[i][h][j]=-1;
            if(s[i][j]!='-')continue;
            for(k=0;k<n;k++)
                map[i][k][j]++;
        }
    return 1;
}
void clear1(char s[25][25],int h)
{
    int i,j,k;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            if(s[i][j]=='X')
                map[i][h][j]=0;
            if(s[i][j]!='-')continue;
            for(k=0;k<n;k++)
                map[i][k][j]--;
        }
}
char u[25][25][25];
int go(int x,int y,int z)
{
    if(x<0 || y<0 || z<0 || x>=n || y>=n || z>=n || u[x][y][z] || map[x][y][z]>0)
        return 0;
    u[x][y][z]=1;
    int sum=!!map[x][y][z];
    for(int i=0;i<8;i++)
        sum+=go(x+dx[i],y+dy[i],z+dz[i]);
    return sum;
}
char paint2(char s[25][25],int h)
{
    int i,j,k;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            if(s[i][j]=='X' && map[h][i][j]>0)return 0;
            if(s[i][j]!='-')continue;
            for(k=0;k<n;k++)
                if(map[k][i][j]<0)return 0;
        }
    return 1;
    int sum=0;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            for(k=0;k<n;k++)
            {
                u[i][j][k]=0;
                if(map[i][j][k])sum++;
            }
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            for(k=0;k<n;k++)
                if(map[i][j][k])
                    return go(i,j,k)==sum;
}
char s0[25][25],s1[25][25],s2[25][25];
main()
{
    int i,j,k,h0,h1,h2,C=1;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<25;i++)
            for(j=0;j<25;j++)
                for(k=0;k<25;k++)
                    map[i][j][k]=0;
        for(i=0;i<n;i++)
            scanf("%s",s0[i]);
        for(i=0;i<n;i++)
            scanf("%s",s1[i]);
        for(i=0;i<n;i++)
            scanf("%s",s2[i]);
        printf("Data set %d: ",C++);
        for(i=0;i<4;i++,rotate(s0))
            for(h0=0;h0<n;h0++)
            {
                paint0(s0,h0);
                for(j=0;j<4;j++,rotate(s1))
                    for(h1=0;h1<n;h1++)
                    {
                        if(!paint1(s1,h1))continue;
                        for(k=0;k<4;k++,rotate(s2))
                            for(h2=0;h2<n;h2++)
                                if(paint2(s2,h2))goto find;
                        clear1(s1,h1);
                    }
                for(j=0;j<4;j++,rotate(s2))
                    for(h1=0;h1<n;h1++)
                    {
                        if(!paint1(s2,h1))continue;
                        for(k=0;k<4;k++,rotate(s1))
                            for(h2=0;h2<n;h2++)
                                if(paint2(s1,h2))goto find;
                        clear1(s2,h1);
                    }
                paint0(s0,h0);
            }
        puts("Impossible combination");
        continue;
    find:
        puts("Valid set of patterns");
    }
}
