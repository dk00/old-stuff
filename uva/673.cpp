#include<stdio.h>
#define PUSH(s)   stack[top++]=(s)
#define POP       (stack[--top])
main(){
int n,i,top;
char bal[129],stack[129];
scanf("%d",&n);
gets(bal);
while(n--){
    gets(bal);
    for(top=i=0;bal[i]!='\0';i++){
        if(bal[i]=='(' || bal[i]=='[')PUSH(bal[i]);
        else if(bal[i]-POP>2 || stack[top]>bal[i])break;
    }
    if(!top && !bal[i])printf("Yes\n");
    else printf("No\n");
}
}
