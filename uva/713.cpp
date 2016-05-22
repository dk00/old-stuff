#include"bigint1.h"
char *rev(char a[])
{
    int i,j;
    for(i=0;a[i];i++);
    char c;
    for(j=0,i--;j<i;j++,i--)
        c=a[i],a[i]=a[j],a[j]=c;
    return a;
}
bigint a,b;
main()
{
    int T;
    char s1[205],s2[205];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s %s",s1,s2);
        rev(s1),rev(s2);
        a=s1,b=s2;
        a+=b;
        b=rev(strcpy(s1,a.tostr()));
        puts(b.tostr());
    }
}
