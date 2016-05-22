#include<stdio.h>
#include<string.h>
char c,temp[10000],s[10000];
int r,aeiou[256],lt[256];
char *pig_latin(char *s){
    if(aeiou[*s])return strcat(strcpy(temp,s),"ay");
    strcpy(temp,s+1);
    r=strlen(temp);
    temp[r]=*s;
    temp[r+1]=0;
    return strcat(temp,"ay");
}
main(){
int i,j;
for(i='A';i<='Z';i++)lt[i]=1;
for(i='a';i<='z';i++)lt[i]=1;
aeiou['A']=aeiou['E']=aeiou['I']=aeiou['O']=aeiou['U']=1;
aeiou['a']=aeiou['e']=aeiou['i']=aeiou['o']=aeiou['u']=1;
while(gets(s)!=NULL){
    for(i=0;s[i];i=j){
        while(!lt[s[i]] && s[i])putchar(s[i++]);
        if(!s[i])break;
        for(j=i+1;lt[s[j]];j++);
        c=s[j];
        s[j]=0;
        printf("%s",pig_latin(&s[i]));
        s[j]=c;
    }
    puts("");
}
}
