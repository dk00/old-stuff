#include<stdio.h>
int asc[256],used[256],all;
main(){
char s[10000],c1,c2;
int n,i;
scanf("%d%c",&n,&c1);
while(n--){
    gets(s);
    for(i=0;s[i];i++)asc[s[i]]++;
}
for(c1='a',c2='A';c1<='z';c1++,c2++)all+=(asc[c2]+=asc[c1]);
while(all){
    for(c1=c2='A';c1<='Z';c1++)
        if(asc[c1]>asc[c2])c2=c1;
    printf("%c %d\n",c2,asc[c2]);
    all-=asc[c2];
    asc[c2]=0;
}
scanf(" ");
}
