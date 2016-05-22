#include<cmath>
#include<cstdio>
bool notp[10000008],div[10000008];
int prime[664580];
main()
{
    int i,j,k,l,p=0,n,C=0;
    char tmp[1000];
    for(i=0;i<=3162;i++)
        for(j=i;i*i+j*j<=10000000;j++)
        {
            div[i*i+j*j]=1;
            if(i*i+j*j==221)
                printf("%d %d\n",i,j);
        }
    for(i=3,n=2;i<=10000007;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*3;j<=10000007;j+=i*2)
            notp[j]=1;
        if(div[i])continue;
        prime[p++]=i;
    }
    while(scanf("%s",tmp)==1)
    {
        if(C++)puts("");
        for(i=0;tmp[i];i++);
        if(tmp[i-1]=='!')
        {
            tmp[i-1]=0;
            sscanf(tmp,"%d",&n);
            for(i=j=0;prime[i]<=p && j<50;i++)
            {
                for(k=0,l=n/prime[i];l>0;l/=prime[i])
                    k+=l;
                if(k%2)
                {
                    if(!j++)
                        printf("He is a liar.\n%d",prime[i]);
                    else printf(" %d",prime[i]);
                }
            }
            if(j)puts("");
            else puts("He might be honest.");
        }
        else
        {
            sscanf(tmp,"%d",&n);
            if(div[n])
                puts("He might be honest.");
            else
                puts("He is a liar.");
        }
    }
}
