#include<cstdio>
char pow(char n,int k)
{
    if(!k)
        return 1;
    if(k%2)
        return(pow(n,k-1)*n)%10;
    char tmp=pow(n,k/2);
    return(tmp*tmp%10);
}
main()
{
    int i,n,m,num[10];
    while(scanf("%d %d",&n,&m)==2)
    {
        m=n-m;
        for(i=0;i<10;i++)num[i]=0;
        while(n>0)
        {
            for(i=n%10;i>0;i--)num[i]++;
            for(n/=10,i=1;i<10;i++)num[i]+=n;
        }
        while(m>0)
        {
            for(i=m%10;i>0;i--)num[i]--;
            for(m/=10,i=1;i<10;i++)num[i]-=m;
        }
        num[2]+=2*num[4]+num[6]+3*num[8];
        num[3]+=num[6]+2*num[9];
        if(num[2]>num[5])num[2]-=num[5],num[5]=0;
        else num[5]-=num[2],num[2]=0;
        i=pow(2,num[2]);
        i*=pow(3,num[3]);
        i*=pow(5,num[5]);
        i*=pow(7,num[7]);
        printf("%d %d %d %d\n",num[2],num[3],num[5],num[7]);
        printf("%d\n",i%10);
    }
}
