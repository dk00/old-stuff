#include<cstdio>
int nn,p[1001],u[1001];
void go(int s1[],int s2[],int n)
{
    if(n<=1)
        return;
    int i,j,k,l,t1[1001],t2[1001];
    for(i=1;i<n && (i==1 || s1[i-1]<s1[i]) && p[s1[i]]==0;i++)
    {
        p[s1[i]]=s1[0];
        t1[0]=t2[0]=s1[i];
        for(j=0;s1[i]!=s2[j];j++);
        for(l=1,j++;j<n && (i+1>=n || s1[i]>s1[i+1] || s1[i+1]!=s2[j]);j++)
            u[t2[l++]=s2[j]]=1;
        for(j=0,l=1;j<n;j++)
            if(u[s1[j]])
                t1[l++]=s1[j],u[s1[j]]=0;
        go(t1,t2,l);
    }
}
main()
{
    int i,j,n,nd,s1[1001],s2[1001];
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<n;i++)
            scanf("%d",&s1[i]),p[i]=0;
        for(i=0;i<n;i++)
            scanf("%d",&s2[i]);
        s1[n]=s2[n]=-1;
        go(s1,s2,n);
        for(i=1;i<=n;i++)
        {
            printf("%d:",i);
            for(j=1;j<=n;j++)
                if(p[j]==i)
                    printf(" %d",j);
            puts("");
        }
    }
}
