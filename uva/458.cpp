/* @JUDGE_ID:  58589NF  458  c++  "The Decoder"*/
#include<stdio.h>
int main(){
char line[1000];
const int k=7;
long i;
while(gets(line)!=NULL){
for(i=0;;i++){
    if(line[i]=='\0')
        break;
    printf("%c",(char)((int)line[i]-k));
}
printf("\n");
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
