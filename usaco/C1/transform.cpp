/*
LANG:C++
TASK:transform
*/
#include<cstdio>
void copy(int n,char s1[11][11],char s2[11][11])
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            s1[i][j]=s2[i][j];
}
char tmp[11][11];
void rotate(int n,char s[11][11])
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            tmp[j][n-i-1]=s[i][j];
    copy(n,s,tmp);
}
void ref(int n,char s[11][11])
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            tmp[i][n-j-1]=s[i][j];
    copy(n,s,tmp);
}
bool eq(int n,char s1[11][11],char s2[11][11])
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(s1[i][j]!=s2[i][j])return 0;
    return 1;
}
char s1[11][11],s3[11][11];
main()
{
    freopen("transform.in","r",stdin);
    freopen("transform.out","w",stdout);
    int i,n;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%s",s1[i]);
    for(i=0;i<n;i++)
        scanf("%s",s3[i]);
    for(i=1;i<n;i++)
    {
        rotate(n,s1);
        if(eq(n,s1,s3))
            return printf("%d\n",i),0;
        ref(n,s1);
        if(eq(n,s1,s3))
            return puts("5"),0;
        ref(n,s1);
    }
    rotate(n,s1);
    ref(n,s1);
    if(eq(n,s1,s3))
        return puts("4"),0;
    ref(n,s1);
    if(eq(n,s1,s3))
        return puts("6"),0;
    puts("7");
}
