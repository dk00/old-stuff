#include<cstdio>
void print(char a[],int x)
{
    int i;
    for(i=0;i<32;i++)
        a[31-i]=x%2+'0',x/=2;
    a[32]=a[33]=a[34]=a[35]='0';
    a[36]=0;
}
char u[99];
char test(char a[])
{
    int i,j;
    for(i=0;i<32;i++)
        u[i]=0;
    for(i=j=0;i<5;i++)
        j=(j*2+a[i]-'0')%32;
    u[j]=1;
    for(;a[i];i++)
    {
        j=(j*2+a[i]-'0')%32;
        if(u[j]++)return 0;
    }
    return 1;
}
main()
{
    int i,n;
    char tmp[99];
    while(scanf("%d",&n) && n)
    {
        for(i=134217728/2;i<2147483646;i++)
        {
            print(tmp,i);
            if(test(tmp))break;
        }
        printf("%d\n",i);
        puts(tmp);
    }
}
