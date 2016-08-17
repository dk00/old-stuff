#include<cstdio>
#include<cstring>
char end(char a[],char b[]){return(a[0]=='0' && !a[1] && b[0]=='0' && !b[1]);}
long long num(char s[])
{
    long long i,j;
    for(i=j=0;s[i];i++)
        j=j*2+s[i]-'0';
    return j;
}
int len(long long x)
{
    if(!x)return 0;
    return 1+len(x/2);
}
char *bin(long long x,char s[])
{
    int i,j,k;
    for(j=61;j>0 && !((1ll<<j)&x);j--);
    for(k=0;j>=0;k++,j--)
        s[k]='0'+!!((1ll<<j)&x);
    s[k]=0;
    return s;
}
main()
{
    int i,j,k,l,C=0,la,lb;
    char a[99],b[99],fmt[99];
    while(scanf("%s %s",a,b)==2)
    {
        la=strlen(a);
        lb=strlen(b);
        i=num(a);
        j=num(b);
        k=len(1ll*i*j)>?(la+lb-1);
        sprintf(fmt,"%%%ds\n",k);
        printf(fmt,a);
        printf(fmt,b);
        i=la>?lb;
        for(j=0;j<k-i;j++)
            putchar(' ');
        for(j=0;j<i;j++)
            putchar('-');
        puts("");
        for(i=0;b[i];i++);
        for(j=0;i--;j++)
            if(b[i]=='0')
            {
                for(l=k-j-la;l--;)
                    putchar(' ');
                for(l=la;l--;)
                    putchar('0');
                puts("");
            }
            else
            {
                sprintf(fmt,"%%%ds\n",k-j);
                printf(fmt,a);
            }
        for(l=0;l<k;l++)putchar('-');
        puts("");
        i=num(a),j=num(b);
        sprintf(fmt,"%%%ds\n",k);
        printf(fmt,bin(1ll*i*j,a));
        puts("");
    }
}
