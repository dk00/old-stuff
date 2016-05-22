#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char tonum[256],toch[]={"0123456789ABCDEF"};
main(){
int i,s,r,base1,base2;
char num[10000],show[10000];
for(i=0;i<=9;i++)tonum['0'+i]=i;
for(i=10;i<=15;i++)tonum['A'+i-10]=i;
    while(scanf("%s %d %d",num,&base1,&base2)!=EOF){
        for(s=i=0;num[i]!='\0';i++)s=s*base1+tonum[num[i]];
        for(r=base2;s/r>=base2;r*=base2);
        for(i=0;r;i++,r/=base2){
            show[i]=toch[s/r];
            s%=r;
        }
        show[i]=0;
        if(strlen(show)>7)printf("%7s\n","ERROR");
        else printf("%7s\n",show);
    }
}
