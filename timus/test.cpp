#include<cstdio>
short numcmp(char a[],char b[])
{
    int i,j,k,l;
    for(k=0;a[k]=='0';k++);
    for(l=0;b[l]=='0';l++);
    if(a[k]+b[l]==0)return 0;
    for(i=0;a[i+k] && b[i+l];i++);
    if(a[i+k] || b[i+l])return a[i+k]-(short)b[i+l];
    for(i=0;a[i+k]==b[i+l];i++);
    return a[i+k]-(short)b[i+l];
}
main()
{
    char s1[100],s2[100];
    while(scanf("%s %s",s1,s2)==2)
        printf("%d\n",numcmp(s1,s2));
}
