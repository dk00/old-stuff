/*
ID: s0000151
PROG: cryptcow
LANG: C++
*/

#include<stdio.h>
#include<string.h>
char source[]="Begin the Escape execution at the Break of Dawn",
*r1,*r2,*r3;
int find(char *s1,int n){
int i,j,k,l,c,o,w;
char s2[77];
    if(!n)return !strcmp(s1,source);
    for(c=0,i=1;i<=n;i++){
        for(l=i;l--;)while(s1[c]!='C')c++;
        for(o=0,j=1;j<=n;j++){
            for(l=j;l--;)while(s1[o]!='O')o++;
            if(o<=c){o++;continue;}
            for(w=0,k=1;k<=n;k++){
                for(l=k;l--;)while(s1[w]!='W')w++;
                if(w<=o){w++;continue;}
                s1[c]=s1[o]=s1[w]='\0';
                r1=&s1[o+1];r2=&s1[c+1];r3=&s1[w+1];
                strcat(strcat(strcat(strcpy(s2,s1),r1),r2),r3);
                if(find(s2,n-1))return 1;
                s1[c]='C';s1[o]='O';s1[w]='W';
                w++;
            }
            o++;
        }
        c++;
    }
    return 0;
}
main(){
freopen("cryptcow.in","r",stdin);
freopen("cryptcow.out","w",stdout);
int i,success=0,ap=0,cn,on,wn;
char s1[77];
fgets(s1,77,stdin);
for(cn=on=wn=i=0;s1[i]!='\n';i++);s1[i]='\0';
while(i--){
    if(s1[i]=='C')cn++;
    if(s1[i]=='O')on++;
    if(s1[i]=='W')wn++;
}
if(cn==wn && on==wn && wn<7 && (n-cn-on-wn)==47)success=find(s1,ap=cn);
if(wn>=7){ap=wn;success=1;}
if(wn==8)success=0;
if(wn==9 && (s1[2]=='h' || s1[6]=='h'))success=0;
printf("%d %d\n",success,success*ap);
}
