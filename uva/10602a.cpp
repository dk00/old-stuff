#include<cstdio>
#include<cstring>
char s[200][200];
int o[200],c[200][200];
int cmp(char *a,char *b)
{
    int i;
    for(i=0;a[i]&b[i] && a[i]==b[i];i++);
    return i;
}
main()
{
    int i,j,k,n,t,sum;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(i=sum=0;i<n;i++)
        {
            o[i]=i;
            scanf("%s",s[i]);
            sum+=strlen(s[i]);
            for(j=0;j<n;j++)
                c[i][j]=c[j][i]=cmp(s[i],s[j]);
        }
        for(i=0;i<n-1;i++)
        {
            for(j=i+2;j<n;j++)
                if(c[o[i]][o[j]]>c[o[i]][o[i+1]])
                    k=o[i+1],o[i+1]=o[j],o[j]=k;
            sum-=c[o[i]][o[i+1]];
        }
        printf("%d\n",sum);
        for(i=0;i<n;i++)
            puts(s[o[i]]);
    }
}
