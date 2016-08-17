#include<stdio.h>
long long s[301][301],ans;
main(){
int i,j,k,a,b,c,y;
char s1[10000];
s[0][0]=1;
for(k=1;k<=300;k++)
    for(i=k;i<=300;i++)
        for(j=0;j<i;j++)
            s[i][j+1]+=s[i-k][j];
while(gets(s1)!=NULL){
    y=sscanf(s1,"%d %d %d",&a,&b,&c);
    if(y==1)
        for(ans=i=0;i<=a;i++)ans+=s[a][i];
    if(y==2)
        for(ans=i=0;i<=a && i<=b;i++)ans+=s[a][i];
    if(y==3)
        for(ans=0,i=b;i<=a && i<=c;i++)ans+=s[a][i];
    printf("%I64d\n",ans);
}
}
