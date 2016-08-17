#include<cstdio>
#include<cstdlib>
#include<cstring>
int numcmp(const void *a,const void *b)
{
    return *(char *)a-*(char *)b;
}
int mod(char *s,int a)
{
    int i,j,k;
    char tmp[1000];
    for(i=j=k=0;s[i]!=10;i++)
    {
        k=k*10+s[i];
        tmp[j++]=k/a;
        k%=a;
    }
    if(k)
        return k;
    tmp[j]=10;
    for(j=0;tmp[j]==0;j++);
    for(i=0;tmp[j]!=10;i++,j++)
        s[i]=tmp[j];
    s[i]=10;
    return 0;
}
main()
{
    int i,j,k;
    char a[1002],s[1002];
    while(gets(s) && s[0]!='-')
    {
        if(!s[1])
        {
            printf("1%s\n",s);
            continue;
        }
        for(i=0;s[i];i++)
            s[i]-='0';
        s[i]=10;
        for(i=9,j=0;i>=2;i--)
            while(mod(s,i)==0)
                a[j++]=i+'0';
        if(s[1]!=10)
        {
            puts("There is no such number.");
            continue;
        }
        qsort(a,j,sizeof(a[0]),numcmp);
        a[j]=0;
        puts(a);
    }
}
