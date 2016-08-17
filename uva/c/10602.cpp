#include<cstdio>
#include<cstring>
int dis(char *a,char *b)
{
    int i,j;
    for(i=0;a[i] && b[i] && a[i]==b[i];i++);
    for(j=i;b[j];j++);
    return j-i;
}
char s[200][200];
int o[200],c[200][200];
main()
{
    int i,j,k,n,t,sum;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            o[i]=i;
            scanf("%s",s[i]);
            for(j=0;j<i;j++)
            {
                c[i][j]=dis(s[i],s[j]);
                c[j][i]=dis(s[j],s[i]);
            }
        }
        for(sum=0;s[0][sum];sum++);
        for(i=0;i<n-1;sum+=c[o[i]][o[i+++1]])
            for(j=i+2;j<n;j++)
                if(c[o[i]][o[j]]<c[o[i]][o[i+1]])
                    k=o[i+1],o[i+1]=o[j],o[j]=k;
        printf("%d\n",sum);
        for(i=0;i<n;i++)
            puts(s[o[i]]);
    }
}
