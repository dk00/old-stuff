#include<stdio.h>
char tmp[99999];
main(int m,char **a)
{
    int i,j,k,c;
    freopen(a[1],"r",stdin);
    for(i=0;scanf("%s",tmp)==1;i++);
    freopen(a[1],"r",stdin);
    for(j=k=0;(c=getchar())>=0;k++)
        j+=(c=='\n');
    printf("%d %d %d\n",j,i,k);
}
