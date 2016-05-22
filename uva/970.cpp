#include<cstdio>
int c[9][9],pre[9][9];
int test(int a,int b)
{
    int i,j,k=0;
    for(i=1;i<8;i*=2)
        for(j=1;j<8;j*=2)
            if((a&i)&&(b&j))k|=c[i][j];
    return k;
}
int t[200][200];
main()
{
    int i,j,k,n,m;
    char s[2007];
    c[1][1]=2,c[1][2]=c[2][1]=1,c[1][4]=c[4][1]=4;
    c[2][2]=2,c[2][4]=c[4][2]=2;
    c[4][4]=1;
    for(i=0;i<7;i++)
        for(j=0;j<7;j++)
            pre[i][j]=test(i,j);
    scanf("%d",&n);
    while(n--)
    {
        scanf("%s",s);
        for(m=0;s[m];m++)t[m][m]=(1<<(s[m]-'X'));
        for(i=1;i<=m;i++)
            for(j=0;i+j<m;j++)
            {
                t[j][i+j]=0;
                for(k=j;k<i+j && t[j][i+j]!=7;k++)
                    t[j][i+j]|=pre[t[j][k]][t[k+1][i+j]];
            }
        for(i=4;(t[0][m-1]&i)==0;i/=2);
        if(i==4)puts("Z");
        else if(i==2)puts("Y");
        else puts("X");
    }
}
