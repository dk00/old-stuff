#include<stdio.h>
char r[10000],*s=r+5000;
main(){
int i,n;
scanf("%s %d",s,&n);
puts(s);
while(n--){
    for(i=0;s[i];i++);
    if(s[i-1]!='0'){
        s[-1]=s[i-1];
        s--[i-1]=0;
    }
    else s[i-1]=0;
    puts(s);
}
scanf(" ");
}
