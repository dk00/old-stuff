#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char *s[131072],tmp[524288];
int cmp(const void *a,const void *b)
{
    char *x=*(char **)a,*y=*(char **)b;
    if(x[0]!=y[0] && (x[0]=='-' || y[0]=='-'))
        return x[0]=='-'?-1:1;
    int n0=strlen(x),n1=strlen(y);
    if(n0!=n1)
        return ((n0<n1)^(x[0]=='-' && y[0]=='-'))?-1:1;
    return ((strcmp(x,y)<0)^(x[0]=='-' && y[0]=='-'))?-1:1;
}
main()
{
    int i,n,m;
    while(scanf("%d",&n)>0)
    {
    for(i=m=0;i<n;i++)
    {
        scanf("%s",tmp+m);
        s[i]=tmp+m;
        while(tmp[m])m++;
        m++;
    }
    qsort(s,n,sizeof(s[0]),cmp);
    if(n)printf("%s",s[0]);
    for(i=1;i<n;i++)
        printf(" %s",s[i]);
    puts("");
    }
}
