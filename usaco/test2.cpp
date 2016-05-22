#include<stdio.h>
main(){
char s1[1000],s2[1000];
int i;
gets(s1),gets(s2);
for(i=0;s1[i];i++)
    printf("pt[\'%c\']=%c,",s1[i],s2[i]);
scanf("%d",&i);
}
