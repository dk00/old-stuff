#include<cstdio>
int s[2007];
char s1[10000],s2[10000];
main()
{
    int i,j,k,n,min,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%[^0123456789]",&n,s1);
        for(i=0;i<n;i++)
        {
            for(j=0;;j++)
            {
                scanf("%[0123456789]%[^0123456789]",s1,s2);
                for(k=0;s2[k];k++);
                if(s2[k-1]=='\n')break;
            }
            s[i]=j;
            if(!i)min=s[i];
            min<?=j;
        }
        for(i=0;s[i]!=min;i++);
        printf("%d",i+1);
        for(i++;i<n;i++)
            if(s[i]==min)
                printf(" %d",i+1);
        puts("");
    }
}
