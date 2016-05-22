#include<stdio.h>
main(){
char line[100],s1[100];
int i,j,d,sum,error,digi[100],s2[100];
while(gets(line)!=NULL){
    for(error=j=d=i=0;line[i];i++){
        if(line[i]=='X'){
            if(d==9)digi[d++]=10;
            else error=1;
        }
        if(line[i]>='0' && line[i]<='9')digi[d++]=line[i]-'0';
        if(line[i]!=' ' && line[i]!='-' && line[i]<'0' && line[i]>'9'
        && line[i]!='X'){
            error=1;
        }
        if(line[i]!=' ')s1[j++]=line[i];
    }
    s1[j]=0;
    if(error || d!=10){
        printf("%s is incorrect.\n",s1);
        continue;
    }
    for(i=0;i<d;i++)s2[i]=digi[i]+(i?s2[i-1]:0);
    for(sum=i=0;i<d;i++)sum+=s2[i];
    if(sum%11)printf("%s is incorrect.\n",s1);
    else printf("%s is correct.\n",s1);
}
}
