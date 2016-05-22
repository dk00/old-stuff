#include<cstdio>
char tmp[100][100];
int s[60];
main()
{
    int i,j,n,m,C=1;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<60;i++)s[i]=-1;
        for(i=m=0;i<n;i++)
        {
            scanf("%s",tmp[i]);
            for(j=0;tmp[i][j];j++);
            tmp[i][j-1]=0;
            while(scanf("%d",&j) && j>=0)
                s[j]=i,m++;
        }
        scanf("%d %d",&i,&j);
        printf("Case %d: Peter arrives at stop %d by tram ",C++,j);
        while(s[i%60]<0)i++;
        for(--j%=m;j--;)
            for(i++;s[i%60]<0;i++);
        printf("%s.\n",tmp[s[i%60]]);
    }
}
