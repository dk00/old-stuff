#include<cstdio>
main()
{
    int i,j,n,a,b,T,C=1,s[50];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&i,&j);
        for(n=0;i || j;n++)
        {
            s[n]=(i+j)%2;
            if(s[n]<0)s[n]=-s[n];
            if(s[n])i--;
            a=-(i-j)/2;
            b=-(i+j)/2;
            i=a,j=b;
        }
        printf("Case #%d: ",C++);
        if(!n)putchar('0');
        while(n--)
            printf("%d",s[n]);
        puts("");
    }
}
