#include<cstdio>
char a[]="234567890-=ertyuiop[]\\dfghjkl;\'cvb\
nm,./@#$%^&*()_+ERTYUIOP{}|DFGHJKL:\"CVBNM<>?",
     b[]="`1234567890qwertyuiop[asdfghjklzxcvb\
nm,~!@#$%^&*()QWERTYUIOP{ASDFGHJKLZXCVBNM<",c[128];
main()
{
    int i;
    for(i=0;i<128;i++)c[i]=i;
    for(i=0;a[i];i++)
        c[a[i]]=b[i];
    while((i=getchar())>0)
        putchar(c[i]);
}
