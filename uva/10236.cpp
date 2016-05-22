#include<cmath>
#include<cstdio>
int a[22000],s[22000];
bool notp[250000];
main()
{
    int i,j,n;
    double p,q;
    s[0]=1;
    s[1]=2;
    for(i=3,n=1;n<=22000;i++,i++)
    {
        if(notp[i])
            continue;
        s[n++]=i;
        for(j=i*3;j<250000;j+=i*2)
            notp[j]=1;
    }
    a[0]=2,p=a[1]=3,q=5;
    for(i=5,j=2;j<22000;i++)
    {
        if(i==s[j])
            a[j++]=(int)q;
        q+=p,p=q-p;
        if(q>999999999.5)
            q/=10,p/=10;
    }
    while(scanf("%d",&n)==1)
        printf("%d\n",a[n-1]);
}
