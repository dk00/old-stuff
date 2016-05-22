#include<cstdio>
char s[9][9],u1[9][10],u2[9][10],u3[9][10];
inline void add(char x,char y,char a)
{
    u1[x][a]++;
    u2[y][a]++;
    u3[x/3*3+y/3][a]++;
    s[x][y]=a;
}
inline void sub(char x,char y,char a=0)
{
    a=s[x][y];
    u1[x][a]--;
    u2[y][a]--;
    u3[x/3*3+y/3][a]--;
    s[x][y]=0;
}
inline char test()
{
    char i,j,k;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        {
            if(s[i][j])continue;
            for(k=1;k<=9;k++)
                if(u1[i][k]+u2[j][k]+u3[i/3*3+j/3][k]==0)break;
            if(k>9)return 1;
        }
    return 0;
}
inline int go(int n)
{
    if(n>=81)
    {
        char i,j;
        for(i=0;i<9;i++)
        {
            for(j=0;j<8;j++)
                printf("%d ",s[i][j]);
            printf("%d\n",s[i][j]);
        }
        puts("");
        return 1;
    }
    if(s[n/9][n%9])return go(n+1);
    if(test())return 0;
    int sum=0;
    for(char k=1;k<=9;k++)
        if(u1[n/9][k]+u2[n%9][k]+u3[n/9/3*3+n%9/3][k]==0)
        {
            add(n/9,n%9,k);
            sum+=go(n+1);
            sub(n/9,n%9);
        }
    return sum;
}
main()
{
    char i,j;
    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        {
            scanf("%d",s[i]+j);
            if(s[i])add(i,j,s[i][j]);
        }
    printf("there are a total of %d solution(s).\n",go(0));
}
