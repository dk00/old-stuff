/* @JUDGE_ID:  58589NF  424  C++  "Integer Inquiry"*/
#include<stdio.h>
#include<string.h>
main(){
char line[102];
int s[101],d,i;
for(i=0;i<=100;i++) s[i]=0;
while(gets(line)!=NULL){
    if(line[0]=='0' && line[1]=='\0') break;
    d=100;
    for(i=strlen(line)-1;i>=0;i--)
        s[d--]+=line[i]-'0';
    for(i=100;i>d && i>0;i--){
        if(s[i]>=10){
            s[i]-=10;
            s[i-1]+=1;
        }
    }
}
for(i=0;s[i]==0;i++);
for(;i<=100;i++) printf("%d",s[i]);
printf("\n");
scanf("%d");
return 0;
}
/*@END_OF_SOURCE_CODE*/
