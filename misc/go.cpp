#include<cstdio>
#include<cstdlib>
main(int argc,char **argv)
{
    if(argc!=2)return 0;
    freopen("_go.bat","w",stdout);
    puts("@echo off");
    printf("g%s>%s.in\n",argv[1],argv[1]);
    printf("q%s<%s.in\n",argv[1],argv[1]);
    printf("q%sa<%s.in\n",argv[1],argv[1]);
    system("_go");
}
