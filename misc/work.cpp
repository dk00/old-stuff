#include<cstdio>
const int MaxT=20008;
int s1[MaxT],s2[MaxT];
main()
{
    scanf("%d",&m,&n1,&n2);
    t=m*40;
    while(n1--)
    {
        scanf("%d",&j);
        for(i=j+1;i<=t;i+=j)
            s1[i]++;
    }
    while(n2--)
    {
        scanf("%d",&j);
        for(i=j;i<=t;i+=j)
            s2[i]++;
    }
    for(i=j=0;i+k<t;i++)
    {
        while(j<s2[i])
            j+=s1[i+k++];
        if((n-=s2[i])<=0)break;
        j-=s2[i];
    }
    printf("%d\n",i+k);
}
