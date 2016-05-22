#include<stdio.h>
#include<string.h>
main(){
char name[11][15],s[15];
int money[11],i,n,j,k,p,q,f=1;
while(scanf("%d%c",&n,&s[0])!=EOF){
    if(f)f=0;
    else puts("");
    for(i=0;i<11;i++)money[i]=0;
    for(i=0;i<n;i++)scanf("%s",name[i]);
    for(i=0;i<n;i++){
        scanf("%s",s);
        for(j=0;strcmp(s,name[j]);j++);
        scanf("%d %d%c",&k,&p,&s[0]);
        if(k && p)money[j]-=k-k%p;q=p;
        while(q-- && p){
            scanf("%s",s);
            for(j=0;strcmp(s,name[j]);j++);
            money[j]+=k/p;
        }
    }
    for(i=0;i<n;i++)printf("%s %d\n",name[i],money[i]);
}
}
