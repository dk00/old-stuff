#include<cstdio>
char r[9][10],c[9][10],q[3][3][10];
int s[9][9];
bool check(int x,int y,int n)
{
    if(r[x][n]+c[y][n]+q[x/3][y/3][n]<3)
        return 0;
    int i,j,k;
    for(i=0;i<9;i++)
    {
        for(j=1;j<=9;j++)
            if(s[i][y] ||(j!=n && r[i][j]+c[y][j]+q[i/3][y/3][j]>2))
                break;
        if(j>9 && i!=x)return 0;
        for(j=1;j<=9;j++)
            if(s[x][i] ||(j!=n && r[x][j]+c[i][j]+q[x/3][i/3][j]>2))
                break;
        if(j>9 && i!=y)return 0;
    }
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            if(x/3*3+i==x && y/3*3+j==y)continue;
            for(k=1;k<=9;k++)
                if(s[x/3*3+i][y/3*3+j] ||(k!=n &&
                r[x/3*3+i][k]+c[y/3*3+j][k]+q[x/3][y/3][k]>2))
                    break;
            if(k>9)return 0;
        }
    return 1;
}
void put(int x,int y,int n)
{
    s[x][y]=n;
    r[x][n]--,c[y][n]--,q[x/3][y/3][n]--;
}
void take(int x,int y,int n)
{
    s[x][y]=0;
    r[x][n]++,c[y][n]++,q[x/3][y/3][n]++;
}
int num,_tmp=0;
void print()
{
    int i,j;
    for(i=0;i<9;i++,puts(""))
        for(j=0;j<9;j++)
            printf("%d ",s[i][j]);

}
int go(int v)
{
    _tmp++;
    if(v>=81)
    {
        num++;
        print();
        return 1;
    }
    if(num>1)return 1;
    int x=v/9,y=v%9;
    if(s[x][y]!=0)
        return go(v+1);
    int i,sum=0;
    for(int i=1;sum<2 && i<=9;i++)
        if(check(x,y,i))
        {
            put(x,y,i);
            sum+=go(v+1);
            take(x,y,i);
        }
    return sum;
}
main()
{
    int i,j,C=1;
    while(scanf("%d",&s[0][0])==1)
    {
        for(i=0;i<9;i++)
            for(j=1;j<=9;j++)
                r[i][j]=c[i][j]=q[i/3][i%3][j]=1;
        for(i=0;i<9;i++)
            for(j=0;j<9;j++)
            {
                if(i+j)scanf("%d",&s[i][j]);
                if(s[i][j])
                    put(i,j,s[i][j]);
            }
        for(i=0,j=10;i<9 && j>9;i++)
            for(j=1;j<=9;j++)
                if(r[i][j]<0 || c[i][j]<0 || q[i/3][i%3][j]<0)
                    break;
        if(i<9 || j<=9)
        {
            puts("Illegal.");
            continue;
        }
        num=_tmp=0;
        go(0);
        printf("Case %d: ",C++);
        if(!num)puts("Impossible.");
        else if(num==1)puts("Unique.");
        else puts("Ambiguous.");
        //printf("%d\n",_tmp);
    }
}
