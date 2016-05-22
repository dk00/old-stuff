#include<cstdio>
#include<algorithm>
int s[1000000];
main()
{
    int i,j,k,n,n2;
    char tmp[999];
    while(1)
    {
        n=1;
        if(scanf("%d%c",s,tmp)==EOF)
            break;
        if(tmp[0]!='\n')
            while(scanf("%d%c",s+n++,tmp) && tmp[0]!='\n')
                tmp[0]=0;
        while(scanf("%d%c",&j,tmp) && tmp[0]!='\n')
        {
            for(i=k=0;i<n;i++)
                k=k*j+s[i];
            printf("%d ",k);
        }
        for(i=k=0;i<n;i++)
            k=k*j+s[i];
        printf("%d\n",k);
    }
}
