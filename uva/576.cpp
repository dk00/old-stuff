#include<stdio.h>
#include<string.h>
int aeiouy[256];
main(){
int i,s1,s2,s3;
char line[1000];
aeiouy['a']=1;aeiouy['e']=1;aeiouy['i']=1;
aeiouy['o']=1;aeiouy['u']=1;aeiouy['y']=1;
while(gets(line) && strcmp(line,"e/o/i")){
    for(s1=i=0;line[i]!='/';){
        if(aeiouy[line[i]])
            for(s1++;aeiouy[line[i]];i++);
        else i++;
    }
    for(i++,s2=0;line[i]!='/';){
        if(aeiouy[line[i]])
            for(s2++;aeiouy[line[i]];i++);
        else i++;
    }
    for(s3=0;line[i];){
        if(aeiouy[line[i]])
            for(s3++;aeiouy[line[i]];i++);
        else i++;
    }
    if(s1==5)
        if(s2==7)
            if(s3==5)puts("Y");
            else puts("3");
        else puts("2");
    else puts("1");

}
}
