#include<cstdio>
#include<windows.h>
main()
{
    int a,b;
    HANDLE hPr,hin,hout,hwrite,hread;
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&pi,sizeof(pi));
    ZeroMemory(&si,sizeof(si));
    si.cb=sizeof(si);
    hin=GetStdHandle(STD_INPUT_HANDLE);
    hout=GetStdHandle(STD_OUTPUT_HANDLE);
    hread=CreateFile("add.in",GENERIC_READ,0,NULL,OPEN_EXISTING,
    FILE_ATTRIBUTE_READONLY,NULL);
    hwrite=CreateFile("out",GENERIC_WRITE,0,NULL,OPEN_EXISTING,
    FILE_ATTRIBUTE_READONLY,NULL);
    SetStdHandle(STD_INPUT_HANDLE,hread);
    scanf("%d %d",&a,&b);
    printf("%d %d\n",a,b);
    /*CreateProcess(NULL,"add",NULL,NULL,TRUE,0,NULL,NULL,&si,&pi);
    hPr=pi.hProcess;*/
    SetStdHandle(STD_INPUT_HANDLE,hin);
    SetStdHandle(STD_OUTPUT_HANDLE,hout);
    WaitForSingleObject(&hPr,10000);
    scanf("%d %d",&a,&b);
}
