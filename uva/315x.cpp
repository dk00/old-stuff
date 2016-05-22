#include<stdio.h>
int n,cri,use[1000],link[1000][1000];
int dfs(int p)
{
    use[p]=1;
    int i,r=1;
    for(i=0;i<n;i++)
        if(link[p][i] && !use[i])r+=dfs(i);
    return r;
}
main()
{
    int i,j,k;
    char line[10000],c;
    while(scanf("%d%c",&n,&c) && n)
    {
        for(i=0;i<n;i++)
        {
            use[i]=0;
            for(j=0;j<n;j++)link[i][j]=0;
        }
        while(gets(line) && sscanf(line,"%d",&j) && j)
        {
            i=0;
            while(line[i]>='0' && line[i]<='9' && line[i])i++;
            while(line[i])
            {
                while((line[i]<'0' || line[i]>'9') && line[i])i++;
                for(k=line[i++]-'0';line[i]>='0' && line[i]<='9'
                && line[i];i++)k=k*10+line[i]-'0';
                link[j-1][k-1]=link[k-1][j-1]=1;
                if(!line[i])break;
            }
        }
        for(i=cri=0;i<n;i++)
        {
            for(j=0;j<n;j++)use[j]=0;
            for(j=0;!link[i][j];j++);
            use[i]=1;
            cri+=(dfs(j)!=n-1);
        }
        printf("%d\n",cri);
    }
}
