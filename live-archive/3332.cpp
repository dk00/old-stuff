#include<cstdio>
int gcd(int a,int b)
{
    while((a%=b)&&(b%=a));
    return a+b;
}
main()
{
    int i,j,k,a,b;
    while(scanf("%d %d",&a,&b)==2)
    {
        k=0;
        for(i=1;i<=a;i++)
        {
            int x=0;
            for(j=1;j<=b;j++)
                if(gcd(i,j)==1)
                    k++,x++;
            
        }
        printf("%d\n",k);
    }
        
}
