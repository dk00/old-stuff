#include<cstdio>
#include<algorithm>
main()
{
    int i,j,k,n1,n2;
    double s[100],s1[10],s2[10],max;
    while(scanf("%d %d",&n1,&n2)==2 && n1)
    {
        for(i=0;i<n1;i++)
            scanf("%lf",s1+i);
        for(j=0;j<n2;j++)
            scanf("%lf",s2+j);
        for(i=k=0;i<n1;i++)
            for(j=0;j<n2;j++)
                s[k++]=s1[i]/s2[j];
        std::sort(s,s+k);
        max=s[1]/s[0];
        for(i=2;i<k;i++)
            max>?=s[i]/s[i-1];
        printf("%.2lf\n",max);
    }
}
