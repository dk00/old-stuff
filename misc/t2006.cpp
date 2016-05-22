#include<cstdio>
main()
{
    int i,j,s[2006];
    s[1]=0;
    for(i=2;i<2007;i++)
        for(s[i]=0,j=1;j<5;j++)
            if(i-j*j>=1 && s[i-j*j]==0)
                s[i]=1;
    for(i=0;i<2007;i++)
    {
        printf("%d",s[i]);
        if(i%10==9)puts("");
    }
    scanf("%d",&i);
}
