#include<stdio.h>
#include<string.h>
char s1[1000],s2[1000];
int table[10][4]={{0,0,0,0},{1,1,1,1},{6,2,4,8},{1,3,9,7},
{6,4,6,4},{5,5,5,5},{6,6,6,6},{1,7,9,3},{6,8,4,2},{1,9,1,9},};
main(){
int a,b,l;
while(scanf("%s %s",s1,s2) && (strcmp(s1,"0") || strcmp(s2,"0"))){
    if(!strcmp(s2,"0")){
        puts("1");
        continue;
    }
    a=s1[strlen(s1)-1]-'0';
    l=strlen(s2);
    b=s2[l-1]-'0';
    if(l>1)b+=(s2[l-2]-'0')*10;
    printf("%d\n",table[a][b%4]);
}
}
