#include<cstdio>
int s[100000];
main()
{
    int i,j,k,n,C=1;
    char tmp1[1000],tmp2[1000];
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        printf("Case %d:\n",C++);
        for(i=0;i<n;i=j)
        {
            for(j=i+1;j<n;j++)
                if(s[j]!=s[j-1]+1)break;
            sprintf(tmp1,"%d",s[i]);
            sprintf(tmp2,"%d",s[j-1]);
            printf("0%s",tmp1);
            for(k=0;tmp1[k];k++)
                if(tmp1[k]!=tmp2[k])break;
            if(tmp1[k])
                printf("-%s",tmp2+k);
            puts("\n");
        }
    }
}
