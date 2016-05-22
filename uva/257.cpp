#include<string.h>
#include<stdio.h>
main(){
char line1[256],line2[256],i;
while(scanf("%s",line1)!=EOF){
    for(i=strlen(line1)-1;i>=0;i--)
        line2[strlen(line1)-1-i]=line1[i];
    if(strcmp(line1,line2)==0)
        printf("%s\n",line1);
}
}
