#include<cstdio>
void swap1(int *&a,int *&b,int s[10][10])
{
    int *tmp=a;
    a=b;
    b=tmp;
}
main()
{
    const int max=10007;
    int i,j,k,t,sum,s[2][70][70];
    char c1[70],c2[70],c3[70];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s %s %s",c1+1,c2+1,c3);
        c1[0]=c2[0]='$';
        for(i=0;c1[i];i++)
            for(j=0;c2[j];j++)
                s[0][i][j]=s[1][i][j]=0;
        s[1][0][0]=1;
        for(k=0;c3[k];k++)
        {
            for(i=0;c1[i];i++)
                for(j=sum=0;c2[j];j++)
                {
                    if(c1[i]==c3[k] || c2[j]==c3[k])
                        s[k%2][i][j]=sum;
                    else s[k%2][i][j]=0;
                    sum+=s[1-k%2][i][j],sum%=max;
                }
            for(j=0;c2[j];j++)
                for(i=sum=0;c1[i];i++)
                {
                    if(c1[i]==c3[k] || c2[j]==c3[k])
                        s[k%2][i][j]+=sum,s[k%2][i][j]%=max;
                    sum+=s[1-k%2][i][j],sum%=max;
                }
        }
        for(i=sum=0;c1[i];i++)
            for(j=0;c2[j];j++)
                sum+=s[1-k%2][i][j],sum%=max;
        printf("%d\n",sum);
    }
}
