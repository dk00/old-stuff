#include<stdio.h>
#include<M_apm.h>
main(){
    MAPM s=1;
    char out[10000];
    long i;
    for(i=1;i<=100;i++)s*=i;
    s.toString(out,10000);
    puts(out);
}
