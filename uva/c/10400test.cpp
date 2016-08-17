#include<stdio.h>
main(){
    char line[1000],e;
    long n,r,i;
    while(gets(line)){
    for(i=n=0;line[i]>='0' && line[i]<='9';i++)n=n*10+line[i]-'0';
    while(line[i]!='\0'){
        e=line[i++];
        for(r=0;line[i]>='0' && line[i]<='9';i++)r=r*10+line[i]-'0';
        switch(e){
            case '+':
                n+=r;
            break;
            case '-':
                n-=r;
            break;
            case '*':
                n*=r;
            break;
            case '/':
                n/=r;
            break;
        }
    }
    printf("%ld\n",n);
    }
}
