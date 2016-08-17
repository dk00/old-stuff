#include<stdio.h>
#define MAX 2005
int prime[305],isp[MAX+1];
main(){
int i,j,p,t,ch[256],C;
char c;
isp[prime[0]=2]=isp[prime[p=1]=3]=1;
for(i=5;i<MAX;i+=2){
    for(isp[i]=j=1;prime[j]<=i/prime[j] && isp[i];j++)
        if(i%prime[j]==0)isp[i]=0;
    if(isp[i])prime[++p]=i;
}
scanf("%d%c",&t,&c);
for(C=1;C<=t;C++){
    for(i=0;i<256;i++)ch[i]=0;
    for(scanf("%c",&c);c!='\n';scanf("%c",&c))ch[c]++;
    printf("Case %d: ",C);
    for(p=0,c='0';c<='z';c++)if(isp[ch[c]] && ++p)printf("%c",c);
    if(p) puts("");
    else puts("empty");
}
}
