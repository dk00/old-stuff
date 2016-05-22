#include<stdio.h>
#include<string.h>
char *calc(char *s){
char tmp[1000],*p=s;
    for(;*p!='+' && *p!='-' && *p;p++)
        if(*p=='('){
            int i=1;
            for(p++;i>0;p++){
                if(*p==')')i--;
                if(*p=='(')i++;
            }
            p--;
        }
    if(*p=='+'){
        *p=0;
        return strcat(strcpy(s,strcat(strcpy(tmp,calc(p+1)),calc(s))),"+");
    }
    if(*p=='-'){
        *p=0;
        return strcat(strcpy(s,strcat(strcpy(tmp,calc(p+1)),calc(s))),"-");
    }
    for(p=s;*p!='*' && *p!='/' && *p;p++)
        if(*p=='('){
        int i=1;
            for(p++;i>0;p++){
                if(*p==')')i--;
                if(*p=='(')i++;
            }
            p--;
        }
        if(*p=='*'){
            *p=0;
            return strcat(strcpy(s,strcat(strcpy(tmp,calc(p+1)),calc(s))),"*");
        }
        if(*p=='/'){
            *p=0;
            return strcat(strcpy(s,strcat(strcpy(tmp,calc(p+1)),calc(s))),"/");
        }
    if(*s=='('){
        int i=1;
        for(p=s+1;i>0;p++){
            if(*p==')')i--;
            if(*p=='(')i++;
        }
        *(p-1)=0;
        return calc(s+1);
    }
    return s;
}
main(){
char s[1000],tmp[1000],*p;
int i,t,f=0;
scanf("%d",&t);
gets(tmp);
gets(tmp);
while(gets(tmp)!=NULL && *tmp){
    for(p=tmp+1;gets(p)!=NULL && *p;p++);
    for(i=0;p--!=tmp;i++){
        if(*p=='(')s[i]=')';
        else if(*p==')')s[i]='(';
        else s[i]=*p;
    }
    s[i]=0;
    if(f)puts("");
    else f=1;
    puts(calc(s));
}
}
