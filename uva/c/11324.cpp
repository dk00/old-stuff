#include<cstdio>
char c[1001][1001];
int s1[1001],s2[1001],d[1001],p[1001],h[1001],q[1001];
int find(int v)
{
    if(v==p[v])return v;
    return p[v]=find(p[v]);
}
int uni(int a,int b)
{
    a=find(a);
    b=find(b);
    if(h[a]<h[b])p[a]=b;
    else p[b]=a;
    if(h[a]==h[b])h[a]++;
}
void go(int &a,int &b,int &c)
{
    if(c>a)b=a,a=c;
    else b>?=c;
}
main()
{
    int i,j,k,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            for(j=d[i]=0;j<n;j++)
                c[i][j]=0;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            i--,j--;
            c[i][j]=c[j][i]=1;
            d[i]++,d[j]++;
        }
        for(i=j=0;i<n;i++)
        {
            p[i]=i,h[i]=s1[i]=s2[i]=0;
            if(d[i]==1)
                q[j++]=i,s1[i]=1;
        }
        for(i=0;i<j;i++)
        {
            for(k=0;!c[q[i]][k];k++);
            if(--d[k]==1)
                q[j++]=k;
            go(s1[k],s2[k],s1[q[i]]);
        }
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(c[i][j] && d[i]>1 && d[j]>1)
                    uni(i,j);
        for(i=0;i<n;i++)
            if(find(i)!=i)
            {
                go(s1[p[i]],s2[p[i]],s2[i]);
                go(s1[p[i]],s2[p[i]],s1[i]);
            }
        for(i=j=0;i<n;i++)
            j>?=s1[i]+s2[i];
        printf("%d\n",j);
    }
}
