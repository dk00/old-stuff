#include<cstdio>
char s[1000][1001],p[100][101];
main()
{
    node *ptr;
    int i,j,l,t,n,m,sum;
    scanf("%d",&t);
    while(t--)
    {
        clear(root);
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            scanf("%s",s[i]);
        scanf("%d %d",&m,&j);
        for(i=l=0;i<m;i++)
        {
            scanf("%s",p[i]);
            for(j=k=0;p[i][j];j++)
            {
                while(k>0 && p[i][k]!=j)
                    k=next2[i][k];
                if(p[i][k]==p[i][j])
                    k++;
                next2[i][j]=k;
            }
            while(k>0)
            {
                for(j=0;p[i][j] && p[i][j]==p[k][j];j++);
                if(!p[i][j])break;
                k=next1[k];
            }
            if(!p[i][j])
                k++;
            next1[i]=k;
        }
        for(j=0;s[0][j];j++)
            now[j]=0;
        for(i=0;i<n;i++)
        {

        }
    }
}
