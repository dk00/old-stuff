#include<stdio.h>
#include<string.h>
char s1[1000],s2[1000],_s[]="~!@#$%^&*()_+|`-=\\{}[]:\";\'<>?,./ ";
int upr[256],lwr[256],num[256],spe[256];
int sy(char *s,int n){
int i;
    for(i=0;i<n;i++)
        if(s[i]!=s[n-i-1])return 0;
    return 1;
}
int check(char* s,int n){
int i;
    for(i=n;s[i];i+=n){
        if(strncmp(s,&s[i],n))return 0;
    }
    return 1;
}
int cycle(char *s,int n){
int i;
    for(i=3;i<7;i++){
        if(n%i){
            strncpy(&s[n-n%i-1],s,i);
            s[n+n%i]=0;
        }
        else s[n]=0;
        if(check(s,i))return 1;
    }
    return 0;
}
main(){
freopen("pf.in","r",stdin);
freopen("pf.out","w",stdout);
char s[1000];
char c;
int i,j,k,un,sn,nn,ln;
for(c='A';c<='Z';c++)upr[c]=1;
for(c='a';c<='z';c++)lwr[c]=1;
for(c='0';c<='9';c++)num[c]=1;
for(c=1;_s[c];c++)spe[_s[c]]=1;
while(scanf("%s %s",s1,s2) && strcmp(s1,"END") && strcmp(s2,"END")){
    if(strcmp(s1,s2)){
        puts("Password settings are not consistent.");
        continue;
    }
    if(strlen(s1)<8 || strlen(s2)>12){
        puts("Password should contain 8 to 12 characters.");
        continue;
    }
    strcpy(s,s1);
    for(un=i=0;s[i];i++)
        if(upr[s[i]])un++;
    if(un<1){
        puts("Password should contain at least one upper-case alphabetical character.");
        continue;
    }
    for(ln=i=0;s[i];i++)
        if(lwr[s[i]])ln++;
    if(ln<1){
        puts("Password should contain at least one lower-case alphabetical character.");
        continue;
    }
    for(nn=i=0;s[i];i++)
        if(num[s[i]])nn++;
    if(nn<1){
        puts("Password should contain at least one number.");
        continue;
    }
    for(sn=i=0;s[i];i++)
        if(spe[s[i]])sn++;
    if(sn<1){
        puts("Password should contain at least one special character.");
        continue;
    }
    if(sy(s,strlen(s))){
        puts("Symmetric password is not allowed.");
        continue;
    }
    if(cycle(s,strlen(s))){
        puts("Circular password is not allowed.");
        continue;
    }
    puts("Password is valid.");
}
}
