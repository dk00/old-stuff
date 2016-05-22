#include<cstdio>
class matrix
{
public:
    int n,s[50][50];
    void operator*=(matrix x)
    {
        int i,j,k,s1[50][50];
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                s1[i][j]=s[i][j],s[i][j]=0;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                for(k=0;k<n;k++)
                    s[i][k]=(s[i][k]+s1[i][j]*x.s[j][k])%10;
    }
    void operator+=(matrix x)
    {
        int i,j;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                s[i][j]=(s[i][j]+x.s[i][j])%10;
    }
    void print()
    {
        int i,j;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n-1;j++)
                printf("%d ",s[i][j]);
            printf("%d\n",s[i][j]);
        }
    }
    void get()
    {
        int i,j;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                scanf("%d",&s[i][j]);
    }
    void clear(int k)
    {
        int i,j;n=k;
        for(i=0;i<k;i++)
            for(j=0;j<k;j++)
                s[i][j]=0;
    }
};
matrix s[21];
matrix pow(matrix s0,int k)
{
    if(k==1)return s0;
    if(k%2)
    {
        matrix tmp=pow(s0,k-1);
        tmp*=s0;
        tmp+=s0;
        return tmp;
    }
    s0=pow(s0,k/=2);
    matrix tmp=s0;
    for(int i=0;(1<<i)<=k;i++)
        if(k&(1<<i))tmp*=s[i];
    s0+=tmp;
    return s0;
}
main()
{
    int i,n,m;
    while(scanf("%d %d",&n,&m) && n+m)
    {
        s[0].n=n,s[0].get();
        for(i=1;i<21;i++)
            s[i]=s[i-1],s[i]*=s[i];
        pow(s[0],m).print();
    }
}
