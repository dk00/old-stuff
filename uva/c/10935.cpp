#include<cstdio>
main()
{
    int i,j,n,s[200];
    while(scanf("%d",&n) && n)
    {
        if(n==1)
        {
            puts("Discarded cards:\nRemaining card: 1");
            continue;
        }
        for(i=0;i<n;i++)
            s[i]=i;
        printf("Discarded cards: 1");
        s[n++]=1;
        for(i=2;i+1<n;i++,i++)
        {
            printf(", %d",s[i]+1);
            s[n++]=s[i+1];
        }
        printf("\nRemaining card: %d\n",s[i]+1);
    }
}
