#include<stdio.h>
#include<string.h>
main(){
char s[100],s1[100],s2[100];
int i,k;
gets(s);
while(gets(s) && strcmp(s,"___________")){
    strncpy(s1,s+1,5);
    s1[5]=0;
    strncpy(s2,s+7,3);
    s2[3]=0;
    strcat(s1,s2);
    for(k=i=0;s1[i];i++,k<<=1)k|=(s1[i]=='o');
    putchar(k>>1);
}
puts("");
}
