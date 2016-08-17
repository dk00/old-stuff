#include<cstdio>
char r[9][10],c[9][10],q[3][3][10],s[9][10],u[9][9];
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
    s[x][y]=n+'0';
    r[x][n]--,c[y][n]--,q[x/3][y/3][n]--;
}
void take(int x,int y,int n)
{
    s[x][y]='.';
    r[x][n]++,c[y][n]++,q[x/3][y/3][n]++;
}
bool make(int v)
{
    if(v>=81)return 1;
    int x=v/9,y=v%9;
    if(s[x][y]!='.')
        return make(v+1);
    int i;
    for(int i=1;i<=9;i++)
        if(check(x,y,i))
        {
            put(x,y,i);
            if(make(v+1))
                return 1;
            take(x,y,i);
        }
    return 0;
}
int num;
int go(int v)
{
    if(!v)num=0;
    if(v>=81)
    {
        num++;
        return 1;
    }
    int x=v/9,y=v%9;
    if(s[x][y]!='.')
        return go(v+1);
    int i,sum=0,tmp,last=0;
    for(int i=1;num<2 && i<=9;i++)
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
    int i,j,k,T;
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<9;i++)
            for(j=1;j<=9;j++)
                r[i][j]=c[i][j]=q[i/3][i%3][j]=1;
        for(i=0;i<9;i++)
        {
            scanf("%s",s[i]);
            for(j=0;j<9;j++)
                if(s[i][j]!='.')
                    u[i][j]=0,put(i,j,s[i][j]-'0');
                else u[i][j]=1;
        }
        make(0);
        /*int find=1;
        while(find)
            for(i=find=0;i<9;i++)
                for(j=0;j<9;j++)
                    if(u[i][j] && s[i][j]!='.')
                    {
                        k=s[i][j]-'0';
                        take(i,j,k);
                        go(0);
                        if(num>1)
                        {
                            put(i,j,k);
                            u[i][j]=0;
                        }
                        else find=1;
                    }*/
        for(i=0;i<9;i++)
            puts(s[i]);
    }
}
