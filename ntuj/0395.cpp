#include<cstdio>
const int N=99;
int d[N],p[N];
int find(int v)
{
    if(p[v]==v)return v;
    return p[v]=find(p[v]);
}
int uni(int a,int b)
{
    a=find(a),b=find(b);
    //printf("%d %d\n",a,b);
    p[a]=b;
}
main()
{
    int i,j,n,m,sum;
    char tmp[999];
    while(scanf("%*s %d %d",&m,&n)==2)
    {
        char c=getchar();
        while(c!='\n')c=getchar();
        for(i=0;i<n;i++)p[i]=i,d[i]=0;
        for(i=j=sum=0;i<n;i++)
        {
            c=getchar();
            while(c!='\n')
            {
                while((c<'0' || c>'9') && c!='\n')c=getchar();
                if(c=='\n')break;
                ungetc(c,stdin);
                scanf("%d%c",&j,&c);
                if(j!=i)
                {
                    uni(i,j);
                    d[i]++,d[j]++;
                    sum++;
                }
            }
        }
        scanf("%*s");
        if(m==0)
            for(i=0;d[i]%2==0 && i<n;i++);
        else
            for(i=0;d[i]%2==(!i || i==m) && i<n;i++);
        for(j=1;j<n;j++)
            if(find(j)==find(0))
                d[0]+=d[j];
        if(i>=n && d[0]==sum*2 && find(m)==find(0))
            printf("YES %d\n",sum);
        else
            puts("NO");
        
    }
}
