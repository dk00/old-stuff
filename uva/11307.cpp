#include<cstdio>
int d[10001],st[10001],ed[10001],c[10001],q[10001];
main()
{
    int i,j,k,n,m;
    char tmp[99];
    while(scanf("%d",&n) && n)
    {
        scanf("%d%c",&j,tmp);
        for(i=0;i<n;i++)d[i]=0;
        st[j]=ed[j]=0;
        for(i=-n+2,m=0;i<n;i++)
        {
            scanf("%d%c",&k,tmp);
            if(tmp[0]==':')
            {
                j=k;
                st[j]=ed[j]=m;
                continue;
            }
            d[k]++;
            c[ed[j]++]=k;
        }
        for(i=0;d[i];i++);
        q[0]=i;
        for(i=0,j=1;i<j;i++)
            for(k=st[q[i]];k<ed[q[i]];k++)
                d[c[k]]=1-d[q[i]],q[j++]=c[k];
        for(i=j=k=0;i<n;i++)
            if(d[i])j++;
            else k++;
        printf("%d\n",j+k+(j<?k));
    }
}
