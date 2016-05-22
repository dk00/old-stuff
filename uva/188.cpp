#include<ctype.h>
#include<stdio.h>
int n,s[15];
long long num[15];
int get(){
int i=0;
char c;
    putchar(c=getchar());
    for(i=0;c!='\n' && c!=EOF;i++){
        s[i]=0;
        while(!isalpha(c) && c!='\n' && c!=EOF)
            putchar(c=getchar());
        if(c=='\n' || c==EOF)return i;
        while(isalpha(c)){
            s[i]=(s[i]<<5)|(c-'a'+1);
            putchar(c=getchar());
        }
    }
    return i;
}
int check(long long C){
int i,j,min=C,f=0;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(i!=j && (C/s[i])%n==(C/s[j])%n){
                min>?=(((C/s[i]+1)*s[i])<?((C/s[j]+1)*s[j]));
                f=1;
            }
    if(f)return min>?C;
    return 0;
}
main(){
long long i,min;
while(n=get()){
    for(i=0;i<n;i++)num[i]=s[i];
    while(1){
        for(min=i=0;i<n;i++)
            if(num[i]<num[min])min=i;
        if(i=check(num[min]))num[min]=i;
        else break;
    }
    printf("%d\n\n",num[min]);
}
}
