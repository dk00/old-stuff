#include<stdio.h>
void draw(char *s){
    if(*s>='0' && *s<='9'){
        int re=0;
        while(*s>='0' && *s<='9')re+=*s++-'0';
        if(*s=='b')*s=' ';
        while(re--)putchar(*s);
        draw(s+1);
    }
    else if(*s=='!'){
        puts("");
        draw(s+1);
    }
    else if(!*s)puts("");
}
main(){
char line[10000];
while(gets(line)!=NULL)draw(line);
}
