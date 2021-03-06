#include<stdio.h>
int use[9],p[362880],dx[]={1,0,-1,0},dy[]={0,1,0,-1},
    rev[]={2,3,0,1},
    f[]={40320,5040,720,120,24,6,2,1,0};
char a[]="drul";
class puzzle
{
public:
    int x,y,s[3][3];
    void get()
    {
        int i,j;
        char s1[5];
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
            {
                scanf("%s",s1);
                if(s1[0]=='x')
                    s[x=i][y=j]=0;
                else
                    s[i][j]=s1[0]-'0';
            }
    }
    int check(int n)
    {
        if(x+dx[n]>=0 && x+dx[n]<3 && y+dy[n]>=0 && y+dy[n]<3)
        {
            move(n);
            return 1;
        }
        return 0;
    }
    void move(int n)
    {
        s[x][y]=s[x+dx[n]][y+dy[n]];
        x+=dx[n],y+=dy[n];
        s[x][y]=0;
    }
    int calc(int n=0){
        if(n>=9)return 0;
        int sum=0;
        for(int i=0;i<s[n/3][n%3];i++)
            if(use[i])
                sum+=f[n];
        use[s[n/3][n%3]]=0;
        sum+=calc(n+1);
        use[s[n/3][n%3]]=1;
        return sum;
    }
}test,q[362880];
void dfs(puzzle t)
{
    int k=p[t.calc()];
    if(k==-2)return;
    t.move(k);
    dfs(t);
    putchar(a[k]);
}
main()
{
    int i,j,k,t;
    for(i=0;i<9;i++)
        use[i]=1;
    for(i=0;i<362880;i++)
        p[i]=-1;
    q[0]=(puzzle){2,2,{{1,2,3},{4,5,6},{7,8,0}}};
    p[q[0].calc()]=-2;
    for(i=0,j=1;i<j;i++)
    {
        q[j]=q[i];
        for(k=0;k<4;k++)
            if(q[j].check(k))
                if(p[q[j].calc()]==-1)
                {
                    p[q[j++].calc()]=rev[k];
                    q[j]=q[i];
                }
    }
    scanf("%d",&t);
    while(t--)
    {
        test.get();
        if(p[test.calc()]==-1)
        {
            puts("unsolvable");
            continue;
        }
        dfs(test);
        puts("");
    }
}
