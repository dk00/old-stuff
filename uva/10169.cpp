#include<cstdio>
double s[1000000];
int z[1000000];
main()
{
    int i,j;
    double t;
    s[0]=0,t=1;
    for(i=1,j=0;i<1000000;i++)
    {
        s[i]=s[i-1]+(1-s[i-1])*1.0/i/(i+1);
        t*=1.0/i/(i+1);
        while(t<0.1)t*=10,j++;
        z[i]=j;
    }
    while(scanf("%d",&i)==1)
        printf("%.6lf %d\n",s[i],z[i]);
}
