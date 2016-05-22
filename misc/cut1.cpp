#include<cstdio>
char tmp[64];
main(int m,char **arg)
{
    int i,n;
    if(m<4)return 0;
    FILE *in=fopen(arg[1],"rb"),*out=fopen(arg[2],"wb");
    if(!in || !out)return 0;
    if(s