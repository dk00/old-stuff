#include<stdio.h>
long sum;
struct matrix{
    long h;
    long w;
};
matrix s[26];
long p;
char c,line[1000],*t;
matrix mmul(matrix b,matrix a){
    if(a.w!=b.h){
        a.w=a.h=0;
        return a;
    }
    sum+=a.h*b.h*b.w;
    a.w=b.w;
    return a;
}
matrix dfs(){
    while(line[p]==')')p++;
    if(line[p]=='(' && ++p)return mmul(dfs(),dfs());
    else return s[line[p++]-'A'];
}
main(){
long n,i,j,top;
for(n=0;n<26;n++)s[n].h=s[n].w=0;
scanf("%ld%c",&n,&c);
while(n--){
    scanf("%c %ld %ld%c",&c,&i,&j,&line[0]);
    s[c-'A'].h=i;
    s[c-'A'].w=j;
}
while(gets(line)!=NULL){
    sum=p=0;
    if(dfs().w)printf("%ld\n",sum);
    else puts("error");
}
}
