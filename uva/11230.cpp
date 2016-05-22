#include<cstdio>
#include<cstring>
const int inf=200000000;
char p[101][101],tmp[101];
main()
{
    int i,j,k,n,m,a,b;
    while(scanf("%d %d %d %d",&n,&m,&a,&b) && n+m+a+b)
    {
        memset(p,0,sizeof(p));
        for(i=k=0;i<n;i++)
        {
            scanf("%s",tmp);
            if(k<0)continue;
            for(j=0;j<m;j++)
            {
                tmp[j]=(tmp[j]-'0')^p[i][j];
                if(tmp[j])
                {
                    if(i+a<=n && j+b<=m)
                        p[i][j]^=1,
                        p[i+a][j]^=1,
                        p[i][j+b]^=1,
                        p[i+a][j+b]^=1,k++;
                    else{k=-1;break;}
                }
                p[i+1][j]^=p[i][j];
                p[i][j+1]^=p[i][j];
                p[i+1][j+1]^=p[i][j];
            }
        }
        printf("%d\n",k);
    }
}
