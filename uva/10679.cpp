#include<stdio.h>
#include<string.h>
char s[100001];
main(){
char r[1001];
int t,q;
scanf("%d",&t);
while(t--){
    scanf("%s",s);
    scanf("%d",&q);
    while(q--){
        scanf("%s",r);
        if(strstr(s,r)!=NULL)
            puts("y");
        else
            puts("n");
    }
}
}
