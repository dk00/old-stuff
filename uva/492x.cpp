#include<ctype.h>
#include<stdio.h>
#include<string.h>
int vwl[256];
char s1[10000];
main(){
char c;
int i;
vwl['a']=vwl['e']=vwl['i']=vwl['o']=vwl['u']=1;
vwl['A']=vwl['E']=vwl['I']=vwl['O']=vwl['U']=1;
while(scanf("%c",&c)!=EOF){
    while(!isalpha(c)){
        putchar(c);
        if((c=getchar())==EOF)return 0;
    }
    for(s1[0]=c,i=1;isalpha(c=getchar());i++)
        s1[i]=c;
    s1[i]=0;
    if(vwl[*s1])printf("%say",s1);
    else printf("%s%cay",s1+1,*s1);
    if(c!=EOF)putchar(c);
}
}
