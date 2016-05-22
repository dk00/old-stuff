#include<cstdio>
#include<cstring>
int n,m,bound,next,use;
int path[100][20],c[100][100],s[100],pre[100],able[500][100];
bool dfs(int,int,int);
bool go(int);
main()
{
    int i,j,t,sum;
    char *p,tmp[1000];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d%c",&m,&n,tmp);
        for(i=sum=0;i<n;i++)
            for(j=pre[i]=0;j<n;j++)
                c[i][j]=0;
        for(i=0;i<n;i++)
        {
            gets(tmp);
            sscanf(tmp,"%d",&s[i]);
            p=strtok(tmp," ");
            p=strtok(0," ");
            while(p)
            {
                sscanf(p,"%d",&j);
                c[i][j-1]=1;
                p=strtok(0," ");
            }
            sum+=s[i];
        }
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(c[i][j])
                    pre[i]+=s[j];
        next=sum/m+(sum%m>0);
        do bound=next++;while(!go(0));
        for(i=0;i<bound;i++)
        {
            for(j=0;j<m;j++)
            {
                if(path[i][j])
                    printf("%d ",path[i][j]);
                else
                    printf("  ");
                path[i][j]=0;
            }
            puts("");
        }
    }
}
bool dfs(int t,int d,int i)
{
    if(!use || d>=m)
    {
        if(go(t+1))
            return 1;
        return 0;
    }
    int k;
    for(;i<n;i++)
        if(able[t][i] && s[i])
        {
            path[t][d]=i+1;
            s[i]--;use--;
            for(k=0;k<n;k++)
                if(c[k][i])
                    pre[k]--;
            if(dfs(t,d+1,i))
                return 1;
            for(k=0;k<n;k++)
                if(c[k][i])
                    pre[k]++;
            s[i]++;use++;
            path[t][d]=0;
        }
    return 0;
}
bool go(int t)
{
    if(t>bound)
        return 0;
    int i;
    for(i=0;i<n && !s[i];i++);
    if(i>=n)return 1;
    for(i=use=0;i<n;i++)
        if(pre[i]==0)
            able[t][i]=1,use+=s[i];
        else able[t][i]=0;
    return dfs(t,0,0);
}
