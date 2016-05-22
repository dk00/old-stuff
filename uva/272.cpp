/* @JUDGE_ID:  58589NF  272  c++  "TeX Quotes"*/
#include<stdio.h>
int main(){
char line[10000],qt[2][3];
qt[0][0]='`';
qt[0][1]='`';
qt[0][2]='\0';
qt[1][0]='\'';
qt[1][1]='\'';
qt[1][2]='\0';
long i,p=1,len;
while(gets(line)!=NULL){
for(i=0;;i++){
    if(line[i]=='\0')
        break;
    if(line[i]=='\"')
        printf("%s",qt[p=(p-1)*-1]);
    else
        printf("%c",line[i]);
}
printf("\n");
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
