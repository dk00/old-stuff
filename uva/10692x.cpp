#include<cstdio>
int n,s[20],tmp[20000];
int calc(int p,int k,int m)
{
    int i,j,t,nk,nm;
    printf("\n%d %d\n",k,m);
    s[p]%=m;
    if(s[p]==0)
        s[p]=m;
    if(p==n-1 || s[p]==1)
    {
        if(s[p]>k)
        {
            if((s[p]-k)%m)
                return k+(s[p]-k)%m;
            return k+m;
        }
        return s[p];
    }
    for(j=0;j<m;j++)
        tmp[j]=0;
    for(i=1,j=s[p]%m;tmp[j]==0;i++,j=(j*s[p])%m)
    {
        printf("%d ",j);
        tmp[j]=i;
    }
    nk=tmp[j]-1,nm=i-tmp[j];
    t=calc(p+1,nk,nm);
    for(j=1;j<=k && t--;j*=s[p]);
    if(t<0)
        return j;
    j%=m;
    while(t--)j=(j*s[p])%m;
    if((j-k)%m<0)
        return k+m+(j-k)%m;
    return k+(j-k)%m;
}
main()
{
    int i,m,C=1;
    char tmp[1000];
    while(scanf("%s",tmp) && tmp[0]!='#')
    {
        sscanf(tmp,"%d",&m);
        scanf("%d",&n);
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);
        printf("Case #%d: %d\n",C++,calc(0,0,m));
    }
}
