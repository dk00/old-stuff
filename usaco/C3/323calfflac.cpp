/*
ID: s0000151
PROG: calfflac
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
int pword(char *s,int len){
    if(len==1)return 1;
    if(len==2 && s[0]==s[1])return 1;
    if(s[0]==s[len-1])return pword(&s[1],len-2);
    else return 0;
}
main(){
if(!DEBUG){freopen("calfflac.in","r",stdin);
freopen("calfflac.out","w",stdout);}
char c,r[20005],s[20000],*t[20000],p[20000],asc[256];
int i,j,n,max,start;
for(i=0;i<256;i++)asc[i]=0;
for(c='A';c<='Z';c++)asc[c]=c-'A'+'a';
for(c='a';c<='z';c++)asc[c]=c;
for(i=n=0;scanf("%c",&c)!=EOF;){
    if(asc[c]){
        s[n]=asc[c];
        p[n]=c;
        r[i++]='\0';
        t[n++]=&r[i];
    }
    else r[i++]=c;
}
r[i++]='\0';
for(max=i=0;n>i+max;i++){
    for(j=n,j=n>18000?1920:j;j>i+max;j--){
        if(s[i]==s[j] && pword(&s[i],j-i+1))
            max=j-(start=i)+1;
    }
}
printf("%d\n",max);
for(i=start;i<start+max-1;i++)
    printf("%c%s",p[i],t[i]);
printf("%c\n",p[i]);
if(DEBUG)scanf(" ");
}
