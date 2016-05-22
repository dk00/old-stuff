#include<cstdio>
#include<cstdlib>
main()
{
    char tmp[999];
    unsigned x;
    while(gets(tmp)){
        sscanf(tmp,"%*s 0x%X",&x);
        printf("%032s\n",itoa(x,tmp,2));
    }
}
