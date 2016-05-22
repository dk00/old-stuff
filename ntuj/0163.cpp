#include<cstdio>
#include<algorithm>
int calc(int s[])
{
    int i,sum=0;
    for(i=1;i<4;i++)
        sum+=(s[i-1]-s[i])*(s[i-1]-s[i]);
    return sum;
}
main()
{
    int i,j,a,b,min,s[6];
    while(scanf("%d %d",&a,&b)==2 && a+b)
    {
        min=2147483647;
        for(i=1;i*i<=a;i++)
            if(a%i==0)for(j=1;j*j<=b;j++)
            {
                if(b%j)continue;
                s[0]=i;
                s[1]=a/i;
                s[2]=j;
                s[3]=b/j;
                std::sort(s,s+4);
                min<?=calc(s);
            }
        printf("%d\n",min);
    }
}
