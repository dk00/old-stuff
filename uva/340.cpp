#include<cstdio>
main()
{
    int i,j,a,b,n,s0[1001],s1[1001],u0[15],u1[15],C=1;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<10;i++)u0[i]=0;
        for(i=0;i<n;i++)
            scanf("%d",s0+i),u0[s0[i]]++;
        printf("Game %d:\n",C++);
        while(1)
        {
            for(i=0;i<n;i++)
                scanf("%d",s1+i);
            if(!s1[0])break;
            for(i=0;i<10;i++)u1[i]=0;
            for(i=a=b=0;i<n;i++)
            {
                if(s0[i]==s1[i])a++;
                u1[s1[i]]++;
            }
            for(i=0;i<10;i++)
                b+=(u0[i]<?u1[i]);
            printf("    (%d,%d)\n",a,b-a);
        }
    }
}
