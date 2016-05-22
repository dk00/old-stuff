#include<cstdio>
const int cn=3,h=12,w=6;
int s1[6],s2[6],c[h+1][w],r[6];
long long num[h+1][16000],*num1,*num2;
int rec[h+1][16000][6];
void clean()
{
    static int i,j;
    for(i=1;i<=h;i++)
    {
        for(j=0;j<w;j++)
            scanf("%d",&c[i][j]);
        for(j=0;j<16000;j++)
            num[i][j]=0;
    }
    for(j=0;j<6;j++)
        c[0][j]=1;
    num[0][0]=1;
}
int calc(int *s)
{
    int sum=0;
    int i,j;
    for(i=j=0;i<6;i++)
        if(s2[i]!=cn)
            sum+=s[i]*r[j++];
    return sum;
}
void putp(int *s,int nn,int ci[6])
{
    int i,j;
    for(i=0,j=cn;i<6;i++)
    {
        if(ci[i]==0)
        {
            s[i]=nn%cn;
            nn/=cn;
        }
        else
            s[i]=cn;
    }
}
void make(int n,int ss,long long num)
{
    if(n>=6)
    {
        num2[calc(s2)]+=num;
        return;
    }
    if(c[ss][n]==1)
    {
        s2[n]=cn;
        make(n+1,ss,num);
        return;
    }
    int i;
    for(i=0;i<cn;i++)
        if((n==0 || s2[n-1]!=i) && s1[n]!=i)
        {
            s2[n]=i;
            make(n+1,ss,num);
        }
}
main()
{
    int i,j,n,t;
    long long sum;
    for(i=r[0]=1;i<6;i++)
        r[i]=r[i-1]*cn,rec[0][0][i-1]=cn;
    scanf("%d",&t);
    while(t--)
    {
        clean();
        for(i=1;i<=h;i++)
        {
            for(j=0;j<w;j++)
            {
                if(c[i][j]==1)
                    s2[j]=cn;
                else
                    s2[j]=0;
            }
            num2=num[i];
            for(j=0;j<16000;j++)    //
            {
                if(num[i-1][j]<=0)
                    continue;
                putp(s1,j,c[i-1]);
                make(0,i,num[i-1][j]);
            }
        }
        for(sum=i=j=0;j<16000;j++)
            sum+=num[h][j];
        printf("%I64d\n",sum);
    }
}
