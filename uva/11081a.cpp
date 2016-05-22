#include<cstdio>
int s[2][99][99];
main()
{
    int i,j,k,p,q,sum,T;
    char s1[99],s2[99],s3[99];
    scanf("%d",&T);
    while(T--)
    {
        s1[0]=s2[0]='$';
        scanf("%s %s %s",s1+1,s2+1,s3);
        for(i=0;s1[i];i++)
            for(j=0;s2[j];j++)
                s[0][i][j]=0;
        s[0][0][0]=1;
        for(k=p=0,q=1;s3[k];k++,p=1-p,q=1-q)
        {
            for(i=0;s1[i];i++)
                for(j=sum=0;s2[j];j++)
                {
                    if(s2[j]==s3[k])
                        s[q][i][j]=sum;
                    else
                        s[q][i][j]=0;
                    sum+=s[p][i][j],sum%=10007;
                }
            for(j=0;s2[j];j++)
                for(i=sum=0;s1[i];i++)
                {
                    if(s1[i]==s3[k])
                        s[q][i][j]+=sum,s[q][i][j]%=10007;
                    sum+=s[p][i][j],sum%=10007;
                }
        }
        for(i=sum=0;s1[i];i++)
            for(j=0;s2[j];j++)
                sum+=s[p][i][j],sum%=10007;
        printf("%d\n",sum);
    }
}
