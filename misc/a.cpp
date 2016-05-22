#include<cstdio>
main()
{
    char tmp[99];
    while(~scanf("%s",tmp)){
    tmp[1]++;
    puts(tmp);
    
    printf("%d %d %d\n",(unsigned char)tmp[0],(unsigned char)tmp[1],(unsigned char)tmp[1]+((unsigned char)tmp[0])*256);}
}
