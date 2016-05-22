#include<cstdio>
int n,m,s[700];
char go(int l)
{
    int i,nl,nu;
    for(i=nl=nu=0;nu<m && i<n;i++)
    {
        if(s[i]+nl>l)
            nl=0,nu++;
        if(nu>=m)return 0;
        nl+=s[i];
    }
    return 1;
}
main()
{
    int i,j,k,min;
    while(scanf("%d %d",&n,&m)==2)
    {
        n++,m++;
        for(i=j=k=0;i<n;i++)
        {
            scanf("%d",s+i);
            j>?=s[i],k+=s[i];
        }
        min=k;
        while(j<=k)
        {
            i=(j+k)/2;
            if(go(i))
                k=i-1,min<?=i;
            else
                j=i+1;
        }
        printf("%d\n",min);
    }
}
