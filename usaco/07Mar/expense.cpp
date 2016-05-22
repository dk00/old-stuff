/*
PROG: expense
LANG: C++
ID: s0000151
*/
#include<cstdio>
int s[100001];
main()
{
    freopen("expense.in","r",stdin);
    freopen("expense.out","w",stdout);
    int i,j,k,l,n,m,p,q,r,min;
    scanf("%d %d",&n,&m);
    j=0,k=min=2000000000;
    for(i=0;i<n;i++)
        scanf("%d",&s[i]),j>?=s[i];
    while(j<=k)
    {
        p=(j+k)/2;
        for(i=r=0,q=1;i<n;i++)
        {
            if(r+s[i]>p)r=0,q++;
            r+=s[i];
        }
        if(q>m)j=p+1;
        else
        {
            min<?=p;
            k=p-1;
        }
    }
    printf("%d\n",min);
}
