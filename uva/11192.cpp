#include<cstdio>
char s[1000];
void rev(int i,int n)
{
    int j,k,l;
    for(j=i,k=i+n-1;j<k;j++,k--)
        l=s[j],s[j]=s[k],s[k]=l;
}
main()
{
    int i,n;
    while(scanf("%d",&n) && n)
    {
        scanf("%s",s);
        for(i=0;s[i];i++);
        n=i/n;
        for(i=0;s[i];i+=n)rev(i,n);
        puts(s);
    }
}
