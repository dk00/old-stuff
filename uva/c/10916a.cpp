#include<cmath>
#include<cstdio>
bool notp[1000001];
int pn,p[350000];
double q[350000];
double fact(int n)
{
    int i,j,sum;
    double num=0.0;
    for(i=0;i<pn;i++)
    {
        for(j=n,sum=0;j>0;j/=p[i])
            sum+=j/p[i];
        num+=q[i]*sum;
    }
    return num;
}
int pow(int a,int b)
{
    if(!b)
        return 1;
    if(b%2)
        return pow(a,b-1)*a;
    int tmp=pow(a,b/2);
    return tmp*tmp;
}
main()
{
    int i,j,k,n,ans[23]={0};
    double m;
    p[0]=2;
    for(i=3,pn=1;i<1000001;i++,i++)
    {
        notp[i-1]=1;
        if(notp[i])continue;
        for(j=i*3;j<1000001;j+=i*2)
            notp[j]=1;
        p[pn++]=i;
    }
    for(i=0;i<pn;i++)q[i]=log10(p[i]);
    while(scanf("%d",&n) && n)
    {
        n=(n-1940)/10;
        if(ans[n])
        {
            printf("%d\n",ans[n]);
            continue;
        }
        m=log10(2)*pow(2,n);
        for(k=n,i=0,j=1000000;i<=j;)
        {
            n=(i+j)/2;
            if(fact(n)>m)
                j=n-1;
            else if(fact(n)<m && fact(n+1)>=m)
                break;
            else i=n+1;
        }
        printf("%d\n",ans[k]=n);
    }
}
