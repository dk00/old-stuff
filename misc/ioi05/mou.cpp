#include<stdio.h>
int h[4000001];
main(){
char cmd,c;
int i,n,k,stt,end;
scanf("%d%c",&n,&c);
for(i=0;i<=n;i++)h[i]=0;
while(scanf("%c",&cmd) && cmd!='E'){
    if(cmd=='Q'){
        scanf("%d%c",&k,&c);
        for(i=1;i<=n && (k-=h[i])>=0;i++);
        printf("%d\n",i-1);
    }
    else if(cmd=='I'){
        scanf("%d %d %d%c",&stt,&end,&k,&c);
        for(i=stt;i<=end;i++)h[i]=k;
    }
}
}
