#include"bigintA03.h"
bigint p,q,r,s,test,b[3323];
main()
{
    int i,t;
    char num[1001];
    b[0]=1;
    for(i=1;i<3323;i++)
        b[i]=b[i-1],b[i]*=2;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",num);
        s=num;
        for(i=1661;s<b[i*2];i--);
        p=b[i],q=b[i*2];
        while(i--)
        {
            r=p;
            (r*=b[i+1])+=b[i*2];
            test=q;
            test+=r;
            if(s<test)continue;
            p+=b[i],q+=r;
        }
        puts(p.tostring());
        if(t)puts("");
    }
}
