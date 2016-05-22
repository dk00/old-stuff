#include<cstdio>
int a[100001];
main()
{
    int i;
    a[0]=0,a[1]=1;
    for(i=2;i<100001;i++)
        if(i%2)a[i]=a[i/2]+a[i/2+1];
        else a[i]=a[i/2];
    for(i=1;i<100001;i++)
        if(a[i-1]>a[i])a[i]=a[i-1];
    while(scanf("%d",&i) && i)
        printf("%d\n",a[i]);
}
