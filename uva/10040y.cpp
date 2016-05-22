#include<cstdio>
int a[1000];
void print(int n,int a[])
{
    for(int i=1;i<=n;i++)
        printf("%d",a[i]);
}
main()
{
    int i,j,k,n;
    while(scanf("%d",&n) && n)
    {

        for(i=0;i<=n;i++)a[i]=0;
        printf("0");
        for(i=n;i>1;)
        {
            a[i]++;
            for(j=1;j<=n-i;j++)a[i+j]=a[j];
            if(n%i==0)print(n,a);
            for(i=n;a[i]==1;i--);
        }
        puts("1");
    }
}
