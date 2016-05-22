#include<cstdio>
#include<cstring>
const int inf=200000000;
char w[10001][99];
int read(char p[][99],char tmp[])
{
    int i=0,j,k=0;
    while(tmp[i] && sscanf(tmp+i,"%s%n",p[k++],&j))
        i+=j;
    return k;
}
void printspc(int n)
{
    if(!n)puts("");
    else while(n--)putchar(' ');
}
int len[10001];
int s[10001][81],p[10001][81];
void print(int n,int r)
{
    if(n)
    {
        if(p[n][r]==0)
            print(n-1,0);
        else
            print(n-1,r+p[n][r]+len[n]);
        printspc(p[n][r]);
    }
    printf("%s",w[n]);
}

char tmp[10001];
main()
{
    int i,j,k,n,m;
    while(scanf("%d%c",&m,tmp) && m)
    {
        n=0;
        while(gets(tmp) && tmp[0])
            n+=read(w+n,tmp);
        for(i=0;i<n;i++)
            len[i]=strlen(w[i]);
        for(i=0;i<10000;i++)
            for(j=0;j<=m;j++)
                s[i][j]=inf;
        s[0][m-len[0]]=0;
        len[n]=0;
        for(i=0;i<n;i++)
        {
            if(s[i][0]<inf)
            {
                p[i+1][m-len[i+1]]=0;
                s[i+1][m-len[i+1]]=s[i][0];
            }
            for(j=1;j<=m;j++)
            {
                if(s[i][j]>=inf)continue;
                for(k=1;len[i+1]+k<=j;k++)
                {
                    int tmp=(k-1)*(k-1)+s[i][j];
                    if(tmp<=s[i+1][j-len[i+1]-k])
                    {
                        s[i+1][j-len[i+1]-k]=tmp;
                        p[i+1][j-len[i+1]-k]=k;
                    }
                }
            }
        }
        print(n-1,0);
        puts("\n");
    }
}
