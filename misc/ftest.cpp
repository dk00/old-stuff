#include<cstdio>
unsigned char buff[10000];
main()
{
    int i;
    fread(buff,1,100,stdin);
    for(i=0;i<100;i++)
        printf("%02X ",buff[i]);
}
