#include<ctime>
#include<cstdio>
#include<cstdlib>
main(int arg,char **f)
{
    if(arg<3)return 0;
    char cmd[99];
    if(arg<=3)sprintf(cmd,"%s < %s",f[1],f[2]);
    else sprintf(cmd,"%s < %s >%s",f[1],f[2],f[3]);
    int st=clock();
    system(cmd);
    printf("%d.%03d\n",(st=clock()-st)/1000,st%1000);
}
