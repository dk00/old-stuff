#include<stdio.h>
long sum;
struct matrix{
    long h;
    long w;
};
main(){
matrix s[26],stack[1000];
long n,i,j,top;
char c,line[1000],*t;
for(n=0;n<26;n++)s[n].h=s[n].w=0;
scanf("%ld%c",&n,&c);
while(n--){
    scanf("%c %ld %ld%c",&c,&i,&j,&line[0]);
    s[c-'A'].h=i;
    s[c-'A'].w=j;
}
while(gets(line)!=NULL){
    sum=top=0;
    t=line;
    while(t[0]){
        while(t[0]=='(')t=&t[1];
        if(t[0]==')'){
            sum+=stack[top-2].h*stack[top-2].w*stack[top-1].w;
            if(stack[top-2].w!=stack[top-1].h)break;
            stack[top-2].w=stack[top-1].w;
            top--;
        }
        else{
            stack[top].w=s[t[0]-'A'].w;
            stack[top++].h=s[t[0]-'A'].h;
        }
        t=&t[1];
    }
    if(top>1){
        puts("error");
        continue;
    }
    printf("%ld\n",sum);
}
}
