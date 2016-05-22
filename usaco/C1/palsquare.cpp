/*
PROB:palsquare
LANG:C++
*/
#include<cstdio>
char num[]="0123456789ABCDEFGHIJ",tmp[100];
void print(int n,int b,char a[])
{
    int i;
    for(i=0;n>0;i++,n/=b)
        tmp[i]=num[n%b];
    while(i--)
        *(a++)=tmp[i];
    *(a++)=0;
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
    freopen("palsquare.in","r",stdin);
    freopen("palsquare.out","w",stdout);
    int i,b;
    char s1[100],s2[100];
    scanf("%d",&b);
    for(i=1;i<=300;i++)
    {
        print(i,b,s1);
        print(i*i,b,s2);
        if(pal(s2))
            printf("%s %s\n",s1,s2);
    }
    scanf(" ");
}
