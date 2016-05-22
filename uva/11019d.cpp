#include<cstdio>
char s[1000001],p[1000001];
int eq[256][256],next[1000001];
main()
{
    int i,j,n,m,x,y,t,sum;
    for(i='a';i<='z';i++)
        eq[i][i]=eq['?'][i]=eq[i]['?']=1;
    eq['?']['?']=1;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            scanf("%s",s+i*m);
        scanf("%d %d",&x,&y);
        for(i=0;i<x;i++)
        {
            if(i)
                for(j=i*m-m+y;j<=i*m;j++)
                    p[j]='?';
            scanf("%s",p+i*m);
            next[i]=0;
        }
        for(i=1,j=0;p[i];i++)
        {
            while(j>0 && !eq[p[i]][p[j]])
                j=next[j];
            if(eq[p[i]][p[j]])
                j++;
            next[i+1]=j;
        }
        for(i=j=sum=0;s[i];i++)
        {
            while(j>0 && !eq[s[i]][p[j]])
                j=next[j];
            if(eq[s[i]][p[j]])
                j++;
            if(!p[j])
                sum++;
        }
        printf("%d\n",sum);
    }
}
