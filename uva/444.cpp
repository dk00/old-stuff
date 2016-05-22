#include<stdio.h>
#include<string.h>
main(){
char line[100000];
int i;
while(gets(line)!=NULL){
    if(line[0]>='0' && line[0]<='9')
        for(i=strlen(line)-1;i>0;)
            if(line[i]>='3'){
                putchar((line[i]-'0')*10+line[i-1]-'0');
                i--,i--;
            }
            else{
                putchar((line[i]-'0')*100+(line[i-1]-'0')*10+line[i-2]-'0');
                i--,i--,i--;
            }
    else for(i=strlen(line);i--;)
        if(line[i]<100)printf("%d%d",line[i]%10,line[i]/10);
        else printf("%d%d%d",line[i]%10,(line[i]%100)/10,line[i]/100);
    puts("");
}
}
