#include"bigintA03.h"
bigint tmp,s[10001],p[200];
main()
{
    int i,j;
    p[0]=0;
    for(i=1;i<200;i++)
        p[i]=p[i-1],p[i]*=2,p[i].s[0]+=1;
    s[1]=1;
    for(i=2;i<10001;i++)
    {
        //s[i]=s[i-1]*2+p[1];
        s[i]=s[i-1],s[i]*=2,s[i]+=p[1];
        for(j=i-2;j>0;j--)
        {
            //tmp=s[j]*2+p[i-j];
            tmp=s[j],tmp*=2,tmp+=p[i-j];
            if(tmp<=s[i])
                s[i]=tmp;
            else break;
        }
    }
    while(scanf("%d",&i)==1)
        puts(s[i].tostring());
}
