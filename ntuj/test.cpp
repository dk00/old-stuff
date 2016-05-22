#include<cstdio>
#include<cstring>
const int inf=200000000;
char w[10000][99];
int read(char *w[],char tmp[])
{
    int i,j;
    sscanf(tmp+i,"%s%n",w++,&j);
    i+=j;
}
void printspc(int n)
{
    if(!n)puts("");
    else while(n--)putchar(' ');
}
void print(int n,int r)
{
    if(p[n][r]==0)
        print(n-1,0);
    else
        print(n-1,r-p[n][r]);
    printspc(p[n][r]);
    printf("%s",w[n]);
}
main()
{
    int m;
    while(scanf("%d",&m) && m)
    {
        n=0;
        while(gets(tmp) && tmp[1])
            n+=read(w+n,tmp);
        for(i=0;i<n;i++)
            len[i]=strlen(w[i]);
        for(i=0;i<10000;i++)
            for(j=1;j<=m;j++)
                s[i][j]=inf;
        s[0][m-len[0]]=0;
        for(i=1;i<n;i++)
        {
            p[i][m-len[i]]=0;
            s[i][m-len[i]]=s[i-1][0];
            for(j=1;j<=m;j++)
            {
                if(s[i+1][m-len-k
                for(k=1;len[i]+k<=j;k++)
                {
                    int tmp=k^2+s[i][j];
                    if(tmp<s[i+1][[j-len[i]-k])
                    {
                        s[i+1][j-len[i]-k]=tmp;
                        p[i+1][j-len[i]-k]=k;
                    }
                }
            }
        }
        print(n,0);
    }
}
