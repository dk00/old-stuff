#include<cstdio>
int num1[99][99],num2[99][99],star[99][99];
main()
{
    int i,j,k,p,q,t;
    char s[100];
    scanf("%d",&t);
    gets(s);
    while(t--)
    {
        gets(s);
        for(i=0;s[i];i++)
        {
            for(j=0;s[j];j++)
                num1[i][j]=num2[i][j]=0;
            num2[i][i]=1;
        }
        for(k=1;s[k];k++)
            for(i=0;s[i+k];i++)
            {
                if(s[i]!=s[i+k])continue;
                for(p=i+1;p<i+k;p++)
                {
                    for(q=p;q<i+k;q++)
                    {
                        num1[i][i+k]+=num1[p][q];
                        if(s[i]!=s[p])
                            num1[i][i+k]+=num2[p][q];
                    }
                }
                for(p=1;p<k;p++)
                    for(q=i;
            }
        for(i=k=0;s[i];i++)
        {
            for(j=0;s[j];j++)
            {
                k+=num1[i][j]+num2[i][j];
                printf("(%2d,%2d) ",num1[i][j],num2[i][j]);
            }
            puts("");
        }
        printf("%d\n",k);
    }
}
