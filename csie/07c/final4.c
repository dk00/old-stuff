#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct _
{
    char x[30];
}word;

int cmp(const void *a,const void *b)
{
    return strcmp(((word *)a)->x,((word *)b)->x);
}
void tolow(char a[])
{
    int i;
    for(i=0;a[i];i++)
        if('A'<=a[i] && a[i]<='Z')
            a[i]=a[i]-'A'+'a';
}
word s[500000];
main()
{
    int i,j,k,n;
    for(n=0;scanf("%s",s[n].x)==1;n++)
        tolow(s[n].x);
    qsort(s,n,sizeof(s[0]),cmp);
    for(i=0;i<n;i+=j)
    {
        for(j=1;j<n;j++)
            if(strcmp(s[i].x,s[i+j].x))break;
        printf("%s %d\n",s[i].x,j);
    }
}
