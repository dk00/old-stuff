#include<cstdio>
#include<algorithm>
int s[30001];
int go(int n)
{
    int i,j,k,c1,c2,c3,min;
    for(i=c3=0;i<n;i++)
        if(s[i]!=3)c3++;
    min=c3;
    for(i=j=k=c1=c2=0;i<n;i++)
    {
        if(s[i]!=3)c3--;
        if(s[i]==3)k++;
        else if(s[i]==1)
        {
            c2++;
            if(c2>j)c2=0,c1+=j;
        }
        else j++;
        min<?=c1+c2+c3+k;
    }
    return min;
}
main()
{
    int i,n,t;
    while(scanf("%d",&n)>0)
    {
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        t=go(n);
        for(i=0;i<n-i-1;i++)
            std::swap(s[i],s[n-i-1]);
        t<?=go(n);
        printf("%d\n",t);
    }
}
