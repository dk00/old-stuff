#include<cstdio>
#include<algorithm>
int s[500000];
main()
{
    int i,j,n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&s[i]);
    std::sort(s,s+n);
    for(i=0;;i++)
    {
        for(j=i;j<n;j++)
            if(s[i]!=s[j])break;
        if(j>=n-n/2)break;
        i=j;
    }
    printf("%d\n",s[i]);
}
