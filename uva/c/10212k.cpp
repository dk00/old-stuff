#include<cstdio>
const int pow[][4]={{0,0,0,0},{1,1,1,1},{2,4,8,6},{3,9,7,1},{4,6,4,6},
{5,5,5,5},{6,6,6,6},{7,9,3,1},{8,4,2,6},{9,1,9,1}};
void go(int s[],int i)
{
    s[3]+=(i+7)/10;
    s[7]+=(i+3)/10;
    s[9]+=(i+1)/10;
}
void test(int s[],int n)
{
    int i,j;
    go(s,n);
    for(i=n;i>=2;i/=2)
    {
        go(s,i/2);
        for(j=i;j>=5;j/=5)
            go(s,j/5);
    }
    for(i=n;i/=2;)s[2]+=i;
    for(i=n;i/=5;)s[5]+=i;
}
main()
{
    int i,j,n,m,s[10];
    while(scanf("%d %d",&n,&m)==2)
    {
        m=n-m;
        for(j=0;j<10;j++)s[j]=0;
        test(s,m);
        for(j=0;j<10;j++)s[j]*=-1;
        test(s,n);
        if(s[2]<s[5])s[5]-=s[2],s[2]=0;
        else s[2]-=s[5],s[5]=0;
        for(i=j=1;j<10;j++)
            if(s[j])(i*=pow[j][(s[j]+3)%4])%=10;
        printf("%d\n",i);
    }
}
