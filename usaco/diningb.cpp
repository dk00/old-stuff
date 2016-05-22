/*
PROB:diningb
LANG:C++
*/
#include<cstdio>
int s[30001];
main()
{
    freopen("diningb.in","r",stdin);
    freopen("diningb.out","w",stdout);
    int i,j,k,n,min;
    scanf("%d",&n);
    for(i=j=0;i<n;i++)
    {
        scanf("%d",s+i);
        if(s[i]==1)j++;
    }
    min=j;
    for(i=k=0;i<n;i++)
    {
        if(s[i]==1)j--;
        else k++;
        if(j+k<min)min=j+k;
    }
    printf("%d\n",min);
}
