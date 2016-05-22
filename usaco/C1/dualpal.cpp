/*
PROB:dualpal
LANG:C++
*/
#include<cstdio>
char num[]="0123456789ABCDEFGHIJ",tmp[100];
char *print(int n,int b,char a[])
{
    int i;
    char *x=a;
    for(i=0;n>0;i++,n/=b)
        tmp[i]=num[n%b];
    while(i--)
        *(a++)=tmp[i];
    *(a++)=0;
    return x;
}
bool pal(char a[])
{
    int i,j;
    for(i=0;a[i];i++);
    for(j=0,i--;a[j];j++,i--)
        if(a[i]!=a[j])return 0;
    return 1;
}
main()
{
    freopen("dualpal.in","r",stdin);
    freopen("dualpal.out","w",stdout);
    int i,j,k,m;
    char a[100];
    scanf("%d %d",&m,&i);
    for(i++;m>0;i++)
    {
        for(j=k=2;k && j<=10;j++)
            if(pal(print(i,j,a)))k--;
        if(!k)printf("%d\n",i),m--;
    }
    scanf(" ");
}
